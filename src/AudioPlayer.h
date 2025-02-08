#include "Arduino.h"
#include "SDCard.h"
#include "Audio.h"

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#define I2S_BCLK 17
#define I2S_LRC 18
#define I2S_DOUT 16

class AudioPlayer {
public:
  SDCard* sd;
  AudioPlayer();
  void setup(SDCard* sdCard);
  void play(const char* path);
  void loop();
};

#endif
