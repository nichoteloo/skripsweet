/* ----------------- General config -------------------------------- */
/* WiFi */
const char* Wifi_ssid = "INDIHOME SADAR";     // Your WiFi SSID
const char* Wifi_password = "Luw4kWh1te";    // Your WiFi password

/* MQTT */
const char* mqtt_broker           = "192.168.100.75"; // IP address of your MQTT broker
const char* mqtt_username         = "mqtt_username";  // Your MQTT username
const char* mqtt_password         = "mqtt_password";  // Your MQTT password
#define     REPORT_MQTT_SEPARATE  true                // Report each value to its own topic
#define     REPORT_MQTT_JSON      true                // Report all values in a JSON message
const char* status_topic          = "events";         // MQTT topic to report startup

/* Serial */
#define     SERIAL_BAUD_RATE    115200               // Speed for USB serial console