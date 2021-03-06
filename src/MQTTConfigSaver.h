#pragma once

#include <string.h>

struct MqttConfiguration {
  char server[100];
  char topicRoot[100];
  char port[6];

  MqttConfiguration(const char *defaultServer, const char *defaultTopicRoot, const char *defaultPort = "1883") {
    strcpy(server, defaultServer);
    strcpy(topicRoot, defaultTopicRoot);
    strcpy(port, defaultPort);
  }
};

class MQTTConfigSaver {
public:
  void loadConfiguration(MqttConfiguration &conf);
  void saveConfiguration(MqttConfiguration &conf);
  void removeSavedConfig();
};
