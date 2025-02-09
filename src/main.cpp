#include <Arduino.h>
#include "TouchSensor.h"
#include "AudioRecorder.h"
#include "AudioPlayer.h"
#include "Robot.h"

SDCard* sdCard;
TouchSensor touchSensor;
AudioRecorder recorder;
AudioPlayer player;
Robot robot;

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
  touchSensor.setup();
  robot.setup();
  recorder.setup(sdCard);
  player.setup(sdCard);
  Serial.println("Setup complete.");
  player.play("/elevenlabs.mp3");
}

void loop() {
  player.loop();
  if (touchSensor.isTouched()) {
    robot.walkForward();
  }
  recorder.handleRecording();
}
