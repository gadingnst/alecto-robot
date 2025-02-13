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
  bool postBinary(const String& url, File* file, const String& filePath, const String& headers = "");

private:
  bool connectToWiFi();
};

#endif
