#ifndef _AUDIO_H
#define _AUDIO_H

#include <Arduino.h>
#include "Mic.h"
#include "SDCard.h"
// 16bit, monoral, 16000Hz,  linear PCM
class Audio {
  Mic* mic;
  SDCard* sd;
  static const int headerSize = 44;
  static const int i2sBufferSize = 12000;
  char i2sBuffer[i2sBufferSize];
  void CreateWavHeader(byte* header, int waveDataSize);

public:
  static const int wavDataSize = 90000;                   // It must be multiple of dividedWavDataSize. Recording time is about 1.9 second.
  static const int dividedWavDataSize = i2sBufferSize/4;
  char** wavData;                                         // It's divided. Because large continuous memory area can't be allocated in esp32.
  byte paddedHeader[headerSize + 4] = {0};                // The size must be multiple of 3 for Base64 encoding. Additional byte size must be even because wave data is 16bit.

  Audio(SDCard* sdCard, MicType micType = ICS43434);
  ~Audio();
  void Record(const char* fileName = "/recording.wav");
};

#endif // _AUDIO_H