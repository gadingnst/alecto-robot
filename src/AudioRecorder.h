#ifndef _AUDIO_RECORDER_H
#define _AUDIO_RECORDER_H

#include <Arduino.h>
#include "Mic.h"
#include "SDCard.h"
#include <string>

class AudioRecorder {
  Mic* mic;
  SDCard* sd;
  static const int headerSize = 44;
  static const int i2sBufferSize = 12000;
  char i2sBuffer[i2sBufferSize];
  void createWavHeader(byte* header, int waveDataSize);
  File file;
  unsigned long startTime;
  unsigned long maxRecordTime;
  std::string currentFileName;
  std::string lastSavedFileName;

private:
  unsigned int recordedDataSize = 0; 

public:
  static const int wavDataSize = 90000;
  static const int dividedWavDataSize = i2sBufferSize/4;
  char** wavData;
  byte paddedHeader[headerSize + 4] = {0};
  bool isRecording = false;

  AudioRecorder();
  ~AudioRecorder();
  void setup(SDCard* sdCard, MicType micType = ICS43434);
  void startRecording(const char* fileName, unsigned long maxDuration);
  void stopRecording();
  void processRecording();
  void reset();
  void record(const char* fileName = "/recording.wav", unsigned long durationMs = 30000, int delayMs = 500);
  void handleRecording();
  std::string getLastSavedFileName() { return lastSavedFileName; };
};

#endif // _AUDIO_RECORDER_H
