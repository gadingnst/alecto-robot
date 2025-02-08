#include "AudioRecorder.h"

AudioRecorder::AudioRecorder(SDCard* sdCard, MicType micType) {
  sd = sdCard;
  mic = new Mic(micType);
  wavData = new char*[wavDataSize / dividedWavDataSize];
  for (int i = 0; i < wavDataSize / dividedWavDataSize; ++i) 
    wavData[i] = new char[dividedWavDataSize];
}

void AudioRecorder::StartRecording(const char* fileName, unsigned long maxDuration) {
  if (isRecording) return;

  Serial.println("Recording started...");
  CreateWavHeader(paddedHeader, wavDataSize);
  sd->begin();
  file = sd->openWavFile(fileName);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  file.write(paddedHeader, headerSize);
  startTime = millis();
  maxRecordTime = maxDuration;
  isRecording = true;
}

void AudioRecorder::StopRecording() {
  if (!isRecording) return;

  Serial.println("Stopping recording...");
  isRecording = false;
  
  CreateWavHeader(paddedHeader, recordedDataSize);
  file.seek(0);
  file.write(paddedHeader, headerSize);
  
  file.close();
  sd->end();
  Serial.println("Recording saved to SD card.");
}

void AudioRecorder::Reset() {
  if (isRecording) {
    StopRecording();
  }
  
  recordedDataSize = 0;
  Serial.println("Audio already reset.");
}

void AudioRecorder::ProcessRecording() {
  if (!isRecording) return;

  int bitPerSample = mic->getBitsPerSample();
  
  if (millis() - startTime >= maxRecordTime) {
    StopRecording();
    return;
  }

  int bytesRead = 0;
  if (bitPerSample == 16) {
    bytesRead = mic->read(i2sBuffer, i2sBufferSize / 2);
    for (int i = 0; i < bytesRead / 4; ++i) {
      wavData[0][2 * i] = i2sBuffer[4 * i + 2];
      wavData[0][2 * i + 1] = i2sBuffer[4 * i + 3];
    }
    file.write((const uint8_t*)wavData[0], bytesRead / 2);
    recordedDataSize += bytesRead / 2; // Tambahkan ukuran data yang ditulis
  } else if (bitPerSample == 32) {
    bytesRead = mic->read(i2sBuffer, i2sBufferSize);
    for (int i = 0; i < bytesRead / 8; ++i) {
      wavData[0][2 * i] = i2sBuffer[8 * i + 2];
      wavData[0][2 * i + 1] = i2sBuffer[8 * i + 3];
    }
    file.write((const uint8_t*)wavData[0], bytesRead / 4);
    recordedDataSize += bytesRead / 4;
  }

  delay(50);  // Tambahkan delay agar data dikumpulkan lebih banyak
}

void AudioRecorder::Record(const char* fileName, unsigned long durationMs) {
  if (!isRecording) {
    Serial.println("\r\nRecording started!\r\n");
    StartRecording(fileName, durationMs);
  } else {
    StopRecording();
    Serial.println("Recording stopped.");
    Reset();
  }
}

void AudioRecorder::HandleRecording() {
  if (isRecording) {
    ProcessRecording();
  }
}

AudioRecorder::~AudioRecorder() {
  for (int i = 0; i < wavDataSize / dividedWavDataSize; ++i) 
    delete[] wavData[i];
  delete[] wavData;
  delete mic;
}

void AudioRecorder::CreateWavHeader(byte* header, int waveDataSize){
  header[0] = 'R';
  header[1] = 'I';
  header[2] = 'F';
  header[3] = 'F';
  unsigned int fileSizeMinus8 = waveDataSize + 44 - 8;
  header[4] = (byte)(fileSizeMinus8 & 0xFF);
  header[5] = (byte)((fileSizeMinus8 >> 8) & 0xFF);
  header[6] = (byte)((fileSizeMinus8 >> 16) & 0xFF);
  header[7] = (byte)((fileSizeMinus8 >> 24) & 0xFF);
  header[8] = 'W';
  header[9] = 'A';
  header[10] = 'V';
  header[11] = 'E';
  header[12] = 'f';
  header[13] = 'm';
  header[14] = 't';
  header[15] = ' ';
  header[16] = 0x10;
  header[17] = 0x00;
  header[18] = 0x00;
  header[19] = 0x00;
  header[20] = 0x01;
  header[21] = 0x00;
  header[22] = 0x01;
  header[23] = 0x00;
  header[24] = 0x80;
  header[25] = 0x3E;
  header[26] = 0x00;
  header[27] = 0x00;
  header[28] = 0x00;
  header[29] = 0x7D;
  header[30] = 0x00;
  header[31] = 0x00;
  header[32] = 0x02;
  header[33] = 0x00;
  header[34] = 0x10;
  header[35] = 0x00;
  header[36] = 'd';
  header[37] = 'a';
  header[38] = 't';
  header[39] = 'a';
  header[40] = (byte)(waveDataSize & 0xFF);
  header[41] = (byte)((waveDataSize >> 8) & 0xFF);
  header[42] = (byte)((waveDataSize >> 16) & 0xFF);
  header[43] = (byte)((waveDataSize >> 24) & 0xFF);
}