#ifndef MIC_H
#define MIC_H

#include <Arduino.h>

#define I2S_SD   10 
#define I2S_WS   11
#define I2S_SCK  12
#define I2S_PORT I2S_NUM_0
#define SAMPLE_RATE 16000
#define BUFFER_SIZE 1024

class Mic {
public:
  static void setup();
  static int16_t read();
};

#endif
