#pragma once

#include <WiFiManager.h>
#include "MQTTConfigSaver.h"
#include <PubSubClient.h>
#include "StreamPrint.h"

void connectWiFi(WiFiManager &wifiManager, MqttConfiguration &mqttConfig, void (*saveConfigCallback)());
void connectMQTT(PubSubClient &mqttClient, MqttConfiguration &mqttConfig, Client &client);
void connectMQTT(PubSubClient &mqttClient, MqttConfiguration &mqttConfig, Client &client, MQTT_CALLBACK_SIGNATURE);
void connectMQTT(PubSubClient &mqttClient, MqttConfiguration &mqttConfig, Client &client, Stream &stream, MQTT_CALLBACK_SIGNATURE);
