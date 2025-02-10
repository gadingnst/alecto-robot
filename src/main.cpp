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
  recorder.setup(sdCard);
  player.setup(sdCard);
  Serial.println("Setup complete.");
}

void loop() {
  player.loop();
  if (touchSensor.isTouched()) {
    recorder.record();
    if (recorder.getLastSavedFileName() != "") {
      Serial.println(recorder.getLastSavedFileName().c_str());
    }
  }
  recorder.handleRecording();
}
