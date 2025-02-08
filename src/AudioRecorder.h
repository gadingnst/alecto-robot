#ifndef _AUDIO_RECORDER_H
#define _AUDIO_RECORDER_H

#include <Arduino.h>
#include "Mic.h"
#include "SDCard.h"

class AudioRecorder {
  Mic* mic;
  SDCard* sd;
  static const int headerSize = 44;
  static const int i2sBufferSize = 12000;
  char i2sBuffer[i2sBufferSize];
  void CreateWavHeader(byte* header, int waveDataSize);
  File file;
  unsigned long startTime;
  unsigned long maxRecordTime;

private:
  unsigned int recordedDataSize = 0; 

public:
  static const int wavDataSize = 90000;
  static const int dividedWavDataSize = i2sBufferSize/4;
  char** wavData;
  byte paddedHeader[headerSize + 4] = {0};
  bool isRecording = false;

  AudioRecorder(SDCard* sdCard, MicType micType = ICS43434);
  ~AudioRecorder();
  void StartRecording(const char* fileName = "/recording.wav", unsigned long maxDuration = 30000);
  void StopRecording();
  void ProcessRecording();
  void Reset();
  void Record(const char* fileName, unsigned long durationMs = 30000);
  void HandleRecording();
};

#endif // _AUDIO_RECORDER_H
