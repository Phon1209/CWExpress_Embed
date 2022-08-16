#ifndef __MQTT_H_
#define __MQTT_H_

#include <PubSubClient.h>
#include "wifi.h"
#include "scheduler.h"

// ----------------------------------
// Client data (unique between clients)
// setup at main.ino
extern const char *mqtt_Client;
extern const char *mqtt_username;
extern const char *mqtt_password;

extern const char *provinceID; // according to HASC standard
extern const char *machineID;

const char *mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;

boolean taskRunning = false;

// Topic Input/ Output
char temp[50];
char taskTopic[50], responseTopic[50], completionTopic[50];

// Forward Declaration
void reconnect();

PubSubClient *mqttClient;
// ----------------------------------
// Pin Setting
#define LED1 4

void setupPinMode()
{
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);
}

// ----------------------------------

void mqttClientNetwork()
{
  if (!mqttClient->connected())
    reconnect();
  mqttClient->loop();
}

Task mqttTask(1 * TASK_MILLISECOND, TASK_FOREVER, &mqttClientNetwork, &taskScheduler, true, NULL, NULL);
// ----------------------------------

void offBlink();
void onBlink();
void blinkComplete();

Task blinkTask(300, TASK_ONCE, &onBlink, &taskScheduler, false, NULL, &blinkComplete);
void onBlink()
{
  Serial.println("LED: on");
  digitalWrite(LED1, HIGH);
  blinkTask.setCallback(&offBlink);
}
void offBlink()
{
  Serial.println("LED: off");
  digitalWrite(LED1, LOW);
  blinkTask.setCallback(&onBlink);
}
void blinkComplete()
{
  currentTask._done = true;
  taskRunning = false;
  sprintf(temp, "%d second task completed, now has %d tasks left",
          currentTask._amount, taskQueue->numElements(taskQueue));
  Serial.println(temp);
  mqttClient->publish(completionTopic, temp);
}
// ----------------------------------

void executeTask()
{
  if (taskQueue->isEmpty(taskQueue) || taskRunning)
    return;

  taskQueue->pull(taskQueue, &currentTask);
  taskRunning = true;

  Serial.print("Receive a task: ");
  Serial.println(currentTask._amount);

  // on and off each count as one iteration
  blinkTask.setIterations(currentTask._amount * 2);
  blinkTask.restart();
  blinkTask.enable();
}
Task processTask(100, TASK_FOREVER, &executeTask, &taskScheduler, true, NULL, NULL);

// ----------------------------------

// ----------------------------------
// MQTT method

void reconnect()
{
  while (!mqttClient->connected())
  {
    Serial.print("Attempting MQTT connection…");
    if (mqttClient->connect(mqtt_Client, mqtt_username, mqtt_password))
    {
      Serial.println("connected");
      mqttClient->subscribe(taskTopic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient->state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++)
    message = message + (char)payload[i];
  Serial.println(message);

  if (!strcmp(topic, taskTopic))
  {
    CWTask newTask;
    if (!createTask(newTask, message))
      return;
    int queueNumber = taskQueue->add(taskQueue, &newTask);
    Serial.print("at queue: ");
    Serial.println(queueNumber);
    if (queueNumber == -1)
      sprintf(temp, "Queue Full...");
    else
      sprintf(temp, "%d second task received on queue %d", newTask._amount, queueNumber);
    mqttClient->publish(responseTopic, temp);
  }
}

void mqttSetup()
{
  connectWifi();

  Serial.println("Wifi Setup complete.");

  Serial.println("Initiate MQTT setup...");
  mqttClient = new PubSubClient(espClient);
  mqttClient->setServer(mqtt_server, mqtt_port);
  mqttClient->setCallback(callback);

  Serial.println("Setup topic for MQTT...");
  sprintf(temp, "@msg/%s/%s", provinceID, machineID);
  strcpy(taskTopic, temp);
  strcat(taskTopic, "/task");
  strcpy(responseTopic, temp);
  strcat(responseTopic, "/response");
  strcpy(completionTopic, temp);
  strcat(completionTopic, "/complete");

  Serial.println("MQTT Setup complete.");

  Serial.print("task topic: ");
  Serial.println(taskTopic);

  Serial.print("response topic: ");
  Serial.println(responseTopic);

  Serial.print("completion topic: ");
  Serial.println(completionTopic);
}

#endif
