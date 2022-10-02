#include "mqtt.h"
#include "monitor.h"
#include "env.h"

// Wifi and MQTT

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
