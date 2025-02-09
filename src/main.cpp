#include <Arduino.h>
#include "TouchSensor.h"
#include "AudioRecorder.h"
#include "AudioPlayer.h"
// #include "Display.h"

SDCard* sdCard;
TouchSensor touchSensor;
AudioRecorder recorder;
AudioPlayer player;
// Display display;

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
//   display.setup();
  touchSensor.setup();
  recorder.setup(sdCard);
  player.setup(sdCard);
  Serial.println("Setup complete.");
  player.play("/elevenlabs.mp3");
}

void loop() {
//   display.idle();
  if (touchSensor.isTouched()) {
    Serial.println("Touched");
    delay(1000);
  }
  player.loop();
} 