#ifndef __WIFI_H_
#define __WIFI_H_

#include <ESP8266WiFi.h>

WiFiClient espClient;

// ----------------------------------
// Wifi

extern const char *ssid;
extern const char *password;

void connectWifi()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// ----------------------------------

#endif