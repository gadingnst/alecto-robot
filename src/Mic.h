#ifndef MIC_H
#define MIC_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"

#define I2S_SD   10 
#define I2S_WS   11
#define I2S_SCK  12
#define I2S_PORT I2S_NUM_0
#define SAMPLE_RATE 16000
#define BUFFER_SIZE 1024

enum MicType {
  ADMP441,
  ICS43434,
  M5GO,
  M5STACKFIRE
};

class Mic {
private:
  i2s_bits_per_sample_t _bitsPerSample;
  MicType _micType;
  bool _isAlreadyInitialized = false;

public:
  Mic(MicType micType);
  void setup();
  int read(char* data, int numData);
  int getBitsPerSample();
};

#endif