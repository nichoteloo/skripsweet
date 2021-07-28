// Set as Access Point (Router 4)

#include <WiFi.h>

const char* Apssid = "ESP32-AP-4";
const char* Appassword = "12345678";

WiFiServer server(80);

void setup() {

    Serial.begin(115200);
    Serial.println("Configuring access point...");

    WiFi.mode(WIFI_AP);
    WiFi.softAP(Apssid, Appassword);
    Serial.println("Wait 100 ms for AP_4_START...");
    delay(100);

    Serial.println("Set softAPConfig");
    IPAddress Ip(192, 168, 43, 84);
    IPAddress Gateway(192, 168, 43, 1);
    IPAddress Subnet(255, 255, 255, 0);
    WiFi.softAPConfig(Ip, Gateway, Subnet);

    if (!WiFi.softAPConfig(Ip,Gateway,Subnet)) {
    Serial.println("AP 4 Failed to configure");
    }

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP 4 IP Address : ");
    Serial.println(IP);

    server.begin();
}

void loop() {

}