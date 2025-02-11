#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {}

void AudioPlayer::setup(SDCard* sdCard) {
  sd = sdCard;
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(75);
  audio.setTone(0,0,0);
  audio.forceMono(true);
  Serial.println("AudioPlayer initialized");
}

void AudioPlayer::play(const char* path) {
  sd->begin();
  if (!sd->exists(path)) {
    Serial.println("File not found on SD Card!");
    return;
  }

  String fullPath = String("/sdcard") + path;
  Serial.print("Playing: ");
  Serial.println(fullPath);

  // Add file information
  File file = sd->getSDMMC().open(path);
  if(file) {
    Serial.print("File size: ");
    Serial.print(file.size());
    Serial.println(" bytes");
    file.close();
  }

  if (!audio.connecttoFS(sd->getSDMMC(), path)) {
    Serial.println("Failed to connect to audio file");
    return;
  }
  Serial.println("Successfully connected to audio file");
}

void AudioPlayer::stop() {
  audio.stopSong();
}

void AudioPlayer::loop() {
  audio.loop();
}
