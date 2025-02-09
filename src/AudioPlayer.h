#include "Arduino.h"
#include "SDCard.h"
#include "Audio.h"

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#define I2S_BCLK 17 // white wire
#define I2S_LRC 18 // grey wire
#define I2S_DOUT 16 // black wire

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
