#ifndef HTTP_H
#define HTTP_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <SDCard.h>

#define WIFI_SSID "esp32"
#define WIFI_PASSWORD "gading18"

class Http {
  SDCard* sd;

public:
  Http();
  void setup(SDCard* sd);
  bool post(const String& url, const String& body, const String& headers = "");
  bool postBinary(const String& url, const uint8_t* data, size_t length, const String& filePath, const String& headers = "");

private:
  bool connectToWiFi();
};

#endif
