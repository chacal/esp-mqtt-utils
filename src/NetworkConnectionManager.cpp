#include "NetworkConnectionManager.h"


void connectWiFi(WiFiManager &wifiManager, MqttConfiguration &mqttConfig, void (*saveConfigCallback)()) {
  Serial << "Connecting to WiFi.." << endl;

  WiFiManagerParameter serverParam("server", "MQTT server", mqttConfig.server, 100);
  WiFiManagerParameter portParam("port", "MQTT port", mqttConfig.port, 6);
  WiFiManagerParameter topicRootParam("topic_root", "MQTT topic root", mqttConfig.topicRoot, 100);

  wifiManager.addParameter(&serverParam);
  wifiManager.addParameter(&portParam);
  wifiManager.addParameter(&topicRootParam);

  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.setConfigPortalTimeout(180);

  if(!wifiManager.autoConnect("ESP8266-Setup")) {
    Serial << "Timeout while trying to establish WiFi connection. Rebooting.." << endl;
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  strcpy(mqttConfig.server, serverParam.getValue());
  strcpy(mqttConfig.topicRoot, topicRootParam.getValue());
  strcpy(mqttConfig.port, portParam.getValue());

  Serial << endl
         << "Connected to WiFi: " << WiFi.SSID() << endl
         << "IP address: " << WiFi.localIP() << endl;
}

void connectMQTT(PubSubClient &mqttClient, MqttConfiguration &mqttConfig, Client &client) {
  mqttClient.setServer(mqttConfig.server, (uint16_t)atoi(mqttConfig.port));
  mqttClient.setClient(client);

  // Loop until we're connected
  while(!mqttClient.connected()) {
    String clientId = "ESP8266Client-" + String(random(0xffff), HEX);

    Serial << "Connecting to " << mqttConfig.server << ":" << mqttConfig.port << " as " << clientId << endl;

    if(mqttClient.connect(clientId.c_str())) {
      Serial << "MQTT Connected." <<  endl;
    } else {
      Serial << "MQTT connection failed, rc=" << mqttClient.state() << " trying again in 5 seconds" << endl;
      delay(5000);
    }
  }
}

void connectMQTT(PubSubClient &mqttClient, MqttConfiguration &mqttConfig, Client &client, MQTT_CALLBACK_SIGNATURE) {
  mqttClient.setCallback(callback);
  connectMQTT(mqttClient, mqttConfig, client);
}

void connectMQTT(PubSubClient &mqttClient, MqttConfiguration &mqttConfig, Client &client, Stream &stream, MQTT_CALLBACK_SIGNATURE) {
  mqttClient.setStream(stream);
  connectMQTT(mqttClient, mqttConfig, client, callback);
}
