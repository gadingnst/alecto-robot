#include <Arduino.h>
#include "TouchSensor.h"
#include "AudioRecorder.h"
#include "AudioPlayer.h"
#include "Robot.h"
#include "Ultrasonic.h"

SDCard* sdCard;
TouchSensor touchSensor;
AudioRecorder recorder;
AudioPlayer player;
Robot robot;
Ultrasonic ultrasonic;

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
  touchSensor.setup();
  ultrasonic.setup();
  robot.setup();
  // recorder.setup(sdCard);
  // player.setup(sdCard);
  // Serial.println("Setup complete.");
  // player.play("/elevenlabs.mp3");
}

void loop() {
  // player.loop();
  // if (touchSensor.isTouched()) {
  //   robot.walkForward();
  // }
  // recorder.handleRecording();
  // robot.walkForward();
  // if (ultrasonic.isObjectClose(10)) {
  //   robot.turnLeft();
  // }
  robot.walkForward();
  if (ultrasonic.isObjectClose(10)) {
    robot.stop();
    delay(1000);
    robot.turnLeft();
    delay(1000);
    robot.turnLeft();
    delay(1000);
  }
}
