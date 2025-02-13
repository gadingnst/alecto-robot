#include "Http.h"

Http::Http() {}

void Http::setup(SDCard* sdCard) {
  connectToWiFi();
  sd = sdCard;
}

bool Http::connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    return true;
  }
  Serial.println("\nFailed to connect to WiFi");
  return false;
}

bool Http::post(const String& url, const String& body, const String& headers) {
  if (WiFi.status() != WL_CONNECTED) {
    if (!connectToWiFi()) {
      return false;
    }
  }

  HTTPClient http;
  http.begin(url);
  
  // Set headers if provided
  if (headers.length() > 0) {
    // Parse headers string (format: "Header1: Value1\nHeader2: Value2")
    int start = 0;
    int end = headers.indexOf('\n');
    while (end != -1) {
      String header = headers.substring(start, end);
      int colon = header.indexOf(':');
      if (colon != -1) {
        String headerName = header.substring(0, colon);
        String headerValue = header.substring(colon + 1);
        headerValue.trim();
        http.addHeader(headerName, headerValue);
      }
      start = end + 1;
      end = headers.indexOf('\n', start);
    }
  }

  int httpResponseCode = http.POST(body);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
    http.end();
    return true;
  } else {
    Serial.println("Error on sending POST: " + String(httpResponseCode));
    http.end();
    return false;
  }
}

bool Http::postBinary(const String& url, const uint8_t* data, size_t length, const String& filePath, const String& headers) {
  if (WiFi.status() != WL_CONNECTED) {
    if (!connectToWiFi()) {
      return false;
    }
  }

  HTTPClient http;
  http.begin(url);
  
  // Set headers if provided
  if (headers.length() > 0) {
    int start = 0;
    int end = headers.indexOf('\n');
    while (end != -1) {
      String header = headers.substring(start, end);
      int colon = header.indexOf(':');
      if (colon != -1) {
        String headerName = header.substring(0, colon);
        String headerValue = header.substring(colon + 1);
        headerValue.trim();
        http.addHeader(headerName, headerValue);
      }
      start = end + 1;
      end = headers.indexOf('\n', start);
    }
  }

  int httpResponseCode = http.POST((uint8_t*)data, length);
  if (httpResponseCode > 0) {
    // Open file for writing
    File file = sd->getSDMMC().open(filePath, FILE_WRITE);
    if (!file) {
      Serial.println("Failed to open file for writing");
      http.end();
      return false;
    }
      
    // Get the response as stream
    WiFiClient* stream = http.getStreamPtr();
      
    // Read all data from server
    while(http.connected()) {
      // Get available data size
      size_t size = stream->available();
      if(size) {
        // Read up to 128 bytes
        uint8_t buff[128] = { 0 };
        int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
        // Write it to file
        file.write(buff, c);
      }
      delay(1);
    }
    
    file.close();
    http.end();
    sd->end();
    Serial.println("File downloaded successfully");
    return true;
  } else {
    Serial.println("Error on sending POST: " + String(httpResponseCode));
    http.end();
    return false;
  }
}