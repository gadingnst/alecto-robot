#ifndef SD_CARD_H
#define SD_CARD_H

#include <SD_MMC.h>

// Pin definitions for ESP32-S3 SD_MMC
#define SD_MMC_CLK 39    // Clock pin
#define SD_MMC_CMD 38    // Command pin
#define SD_MMC_D0  40    // Data pin 0
#define SD_MMC_D1  41    // Data pin 1
#define SD_MMC_D2  42    // Data pin 2
#define SD_MMC_D3  43    // Data pin 3

class SDCard {
private:
  bool _isInitialized;
  void writeWavHeader(File& file, uint32_t dataSize);

public:
  SDCard();
  bool begin();
  bool writeFile(const char* path, const char* message);
  String readFile(const char* path);
  bool appendFile(const char* path, const char* message);
  bool deleteFile(const char* path);
  bool exists(const char* path);
  bool isInitialized() { return _isInitialized; }
  File openWavFile(const char* path);
  bool finalizeWavFile(File& file, uint32_t dataSize);
};

#endif