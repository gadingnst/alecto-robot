#ifndef SPEAKER_H
#define SPEAKER_H

#include <driver/i2s.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include "AudioFileSourceSDMMC.h"

// Pin definitions
#define BCLK_PIN 17   // I2S Serial Clock
#define LRCLK_PIN 18  // I2S Word Select
#define DIN_PIN 40    // I2S Data

// MP3 decoding buffer sizes
#define MP3_BUFFER_SIZE 1024
#define PCM_BUFFER_SIZE 1152

class Speaker {
public:
  Speaker(uint32_t rate = 44100, i2s_bits_per_sample_t bits = I2S_BITS_PER_SAMPLE_16BIT) {
    sampleRate = rate;
    bitsPerSample = bits;
  }
  void setup(SDCard* sdCard);
  bool playMP3File(const char* filename);
  void end();

private:
  uint32_t sampleRate;
  i2s_bits_per_sample_t bitsPerSample;
  AudioOutputI2S* out;
  AudioGeneratorMP3* mp3;
  AudioFileSourceSDMMC* file;
  SDCard* sd;
};

#endif