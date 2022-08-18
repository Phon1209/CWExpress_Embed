#include "mqtt.h"
#include "monitor.h"

// Wifi and MQTT

// char *ssid = "ssid";
// char *password = "password";
// const char *mqtt_Client = "mqtt device id";
// const char *mqtt_username = "mqtt device username";
// const char *mqtt_password = "mqtt password";
// const char *provinceID = "provinceID"; // according to HASC standard
// const char *machineID = "machineID";

void setup()
{
    Serial.begin(115200);
    mqttSetup();
    monitorSetup();
    setupPinMode();
}

void loop()
{
    taskScheduler.execute();
}
