#include "Arduino.h"
#include "SDCard.h"
#include "Audio.h"

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

/**
 * VIN -> 5V -> red wire
 * GND -> GND -> orange wire
 * SD -> Floating -> brown wire 
 * GAIN -> GND -> green wire
 */
#define I2S_BCLK 14  // white wire - Bit Clock
#define I2S_LRC  15  // grey wire  - Word Select
#define I2S_DOUT 13  // black wire - Data Out

class AudioPlayer {
public:
  SDCard* sd;
  Audio audio;
  AudioPlayer();
  void setup(SDCard* sdCard);
  void play(const char* path);
  void loop();
  Audio getAudio() { return audio; };
};

#endif
