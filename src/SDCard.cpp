#include "SDCard.h"
#include "Mic.h"

SDCard::SDCard() {
  _isInitialized = false;
}

bool SDCard::setup() {
  // Configure SD_MMC pins
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0, SD_MMC_D1, SD_MMC_D2, SD_MMC_D3);
  
  // Initialize SD card
  if(!begin()) {
    Serial.println("Failed to initialize SD Card!");
    return false;
  }
  
  // Check card type
  if(SD_MMC.cardType() == CARD_NONE) {
    Serial.println("No SD Card attached!");
    return false;
  }
  
  Serial.println("SD Card initialized");
  return true;
}

bool SDCard::begin() {
  if (_isInitialized) return true;
  _isInitialized = true;
  return SD_MMC.begin("/sdcard", true);
}

void SDCard::end() {
  if (!_isInitialized) return;
  _isInitialized = false;
  SD_MMC.end();
}

bool SDCard::writeFile(const char* path, const char* message) {
  if (!_isInitialized) return false;
  
  File file = SD_MMC.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing!");
    return false;
  }
  
  bool success = file.print(message);
  file.close();
  return success;
}

String SDCard::readFile(const char* path) {
  if (!_isInitialized) return "";
  
  File file = SD_MMC.open(path);
  if(!file) {
    Serial.println("Failed to open file for reading!");
    return "";
  }
  
  String content = "";
  while(file.available()) {
    content += (char)file.read();
  }
  file.close();
  return content;
}

bool SDCard::appendFile(const char* path, const char* message) {
  if (!_isInitialized) return false;
  
  File file = SD_MMC.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending!");
    return false;
  }
  
  bool success = file.print(message);
  file.close();
  return success;
}

bool SDCard::deleteFile(const char* path) {
  if (!_isInitialized) return false;
  return SD_MMC.remove(path);
}

bool SDCard::exists(const char* path) {
  if (!_isInitialized) return false;
  return SD_MMC.exists(path);
}

void SDCard::writeWavHeader(File& file, uint32_t dataSize) {
  // RIFF chunk
  file.write((const uint8_t*)"RIFF", 4);
  uint32_t fileSize = dataSize + 36;
  file.write((const uint8_t*)&fileSize, 4);
  file.write((const uint8_t*)"WAVE", 4);
  
  // Format chunk
  file.write((const uint8_t*)"fmt ", 4);
  uint32_t fmtSize = 16;
  file.write((const uint8_t*)&fmtSize, 4);
  uint16_t audioFormat = 1; // PCM
  file.write((const uint8_t*)&audioFormat, 2);
  uint16_t numChannels = 1; // Mono
  file.write((const uint8_t*)&numChannels, 2);
  uint32_t sampleRate = SAMPLE_RATE;
  file.write((const uint8_t*)&sampleRate, 4);
  uint32_t byteRate = SAMPLE_RATE * 2;
  file.write((const uint8_t*)&byteRate, 4);
  uint16_t blockAlign = 2;
  file.write((const uint8_t*)&blockAlign, 2);
  uint16_t bitsPerSample = 16;
  file.write((const uint8_t*)&bitsPerSample, 2);
  
  // Data chunk
  file.write((const uint8_t*)"data", 4);
  file.write((const uint8_t*)&dataSize, 4);
}

File SDCard::openWavFile(const char* path) {
  if (!_isInitialized) return File();
  
  File file = SD_MMC.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open WAV file for writing");
    return File();
  }
  
  // Write initial WAV header with zero size
  writeWavHeader(file, 0);
  return file;
}

bool SDCard::finalizeWavFile(File& file, uint32_t dataSize) {
  Serial.println("Finalizing WAV file...");
  if (!file) {
    Serial.println("Failed to finalize WAV file!");
    return false;
  };
  file.seek(0);
  writeWavHeader(file, dataSize);
  file.close();
  // end();
  Serial.println("WAV file finalized successfully");
  return true;
}