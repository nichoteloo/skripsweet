#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>

const char* Wifi_ssid = "Redmi5A";
const char* Wifi_password = "123456789";

WiFiClient espClient;
PubSubClient client(espClient);

// If only using cloud mqtt broker
// #define MQTT_HOST "example.com"

//Add your MQTT Broker IP address
const char* mqtt_server = "192.168.43.193";
const int mqtt_port = 1883;
const char* mqtt_username = "mqtt_username"; 
const char* mqtt_password = "mqtt_password";

char rss_buffer[255];
unsigned long previousMillis = 0;
const long interval = 5000; 

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    WiFi.begin(Wifi_ssid, Wifi_password); 
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(Wifi_ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); 

    delay(1000);

    client.setServer(mqtt_server, mqtt_port); 

    if (!client.connected()) {
        reconnect();
    }   
}

void loop()
{
    String rssi1 = "";
    String rssi2 = "";
    String rssi3 = "";
    String rssi4 = "";
    String rssiTot = "";
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        if (WiFi.status() == WL_CONNECTED){

            if (!client.connected()) {
                reconnect();
            }

            client.loop();

            int n = WiFi.scanNetworks();
            
            if (n == 0) {
                Serial.println("No networks found");
            } else {
                for (int i = 0; i < n; ++i) {
                    if (WiFi.SSID(i) == "ESP32-AP-1") {
                        rssi1 = rssi1 + String(WiFi.RSSI(i));
//                        rssi2 = rssi2 + String(random(-90,0));
//                        rssi3 = rssi3 + String(random(-90,0));
//                        rssi4 = rssi4 + String(random(-90,0));
                    } 
                     else if (WiFi.SSID(i) == "ESP32-AP-2") {
                         rssi2 = rssi2 + String(WiFi.RSSI(i));  
                     }
                     else if (WiFi.SSID(i) == "ESP32-AP-3") {
                         rssi3 = rssi3 + String(WiFi.RSSI(i));  
                     }
                     else if (WiFi.SSID(i) == "ESP32-AP-4") {
                         rssi4 = rssi4 + String(WiFi.RSSI(i));  
                     }
                }
            }
            
            rssiTot = rssi1 + "," + rssi2 + "," + rssi3 + "," + rssi4;
            Serial.println(rssiTot);

            // client.publish("esp32/rssi/1", (char*) rssi1.c_str());
            // client.publish("esp32/rssi/2", (char*) rssi2.c_str());
            // client.publish("esp32/rssi/3", (char*) rssi3.c_str());
            // client.publish("esp32/rssi/4", (char*) rssi4.c_str());

            // (\") replaced double quote in JSON Parse
            sprintf(rss_buffer, "{\"Client_1\":{\"rssi1\":%s,\"rssi2\":%s,\"rssi3\":%s,\"rssi4\":%s}}",
            rssi1, rssi2, rssi3, rssi4);
            client.publish("esp32/rssi/json", rss_buffer);
            
        }
        else {
            Serial.println("WiFi Disconnected");
        }
    }
    else {
        Serial.println("Timeout 5 sec");
    }
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
        Serial.println("connected");
        } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
        }
    }
}
