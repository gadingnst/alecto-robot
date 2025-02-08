#include "AudioPlayer.h"

Audio audio;

AudioPlayer::AudioPlayer() {}

void AudioPlayer::setup(SDCard* sdCard) {
  sd = sdCard;
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(18);
}

void AudioPlayer::play(const char* path) {
  sd->begin();
  if (!sd->exists(path)) {
    Serial.println("File tidak ditemukan di SD Card!");
    return;
  }

  String fullPath = String("/sdcard") + path;
  Serial.print("Playing: ");
  Serial.println(fullPath);

  audio.connecttoFS(sd->getSDMMC(), path);
}

void AudioPlayer::loop() {
  audio.loop();
}
