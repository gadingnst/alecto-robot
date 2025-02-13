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
    // testConnect();
    return true;
  }
  Serial.println("\nFailed to connect to WiFi");
  return false;
}

void Http::testConnect() {
  String baseUrl = "https://alecto-ai.vercel.app/text-to-speech";
  if (!testConnection(baseUrl)) {
    Serial.println("Failed to connect to base URL");
    if (!testConnection("http://google.com")) {
      Serial.println("Also failed to connect to Google - WiFi issue");
    } else {
      Serial.println("Can reach Google but not your server - server issue");
    }
  }
}

bool Http::testConnection(const String& url) {
  if (WiFi.status() != WL_CONNECTED) {
    if (!connectToWiFi()) {
      return false;
    }
  }

  HTTPClient http;
  if (!http.begin(url)) {
    Serial.println("Failed to begin HTTP connection");
    return false;
  }

  int code = http.GET();
  Serial.println("Test connection response: " + String(code));
  Serial.println("Response: " + http.getString());
  http.end();
  return code > 0;
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

bool Http::postBinary(const String& url, File* file, const String& filePath, const String& headers) {
  if (WiFi.status() != WL_CONNECTED) {
    if (!connectToWiFi()) {
      Serial.println("Failed to connect to WiFi");
      return false;
    }
  }

  HTTPClient http;
  if (!http.begin(url)) {
    Serial.println("Failed to begin HTTP connection");
    return false;
  }
  
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

  size_t fileSize = file->size();
  Serial.println("Sending file of size: " + String(fileSize) + " bytes");
  
  int httpResponseCode = http.sendRequest("POST", file, fileSize);
  
  if (httpResponseCode > 0) {
    Serial.println("Response code: " + String(httpResponseCode));
    File responseFile = sd->getSDMMC().open(filePath, FILE_WRITE);
    if (!responseFile) {
      Serial.println("Failed to open response file for writing");
      http.end();
      return false;
    }
    
    WiFiClient* stream = http.getStreamPtr();
    while (http.connected() && stream->available()) {
      responseFile.write(stream->read());
    }
    
    responseFile.close();
    Serial.println("File downloaded successfully");
    http.end();
    return true;
  } else {
    Serial.println("Error on sending POST: " + String(httpResponseCode));
    Serial.println("Error details: " + http.errorToString(httpResponseCode));
    http.end();
    return false;
  }
}
