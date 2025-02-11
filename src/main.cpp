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

// task declaration
void Task1(void *parameter);
void Task2(void *parameter);
void Task3(void *parameter);

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
  player.play("/elevenlabs-sample-1.mp3");

  // create task
  xTaskCreate(
    Task1,    // task function
    "Task1",  // task name
    10000,    // stack size
    NULL,     // parameter
    1,        // priority
    NULL      // task handle
  );

  xTaskCreate(
    Task2,
    "Task2",
    10000,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    Task3,
    "Task3",
    10000,
    NULL,
    1,
    NULL
  );
}

void loop() {
  // main loop can be empty because the task is running by itself
  vTaskDelay(pdMS_TO_TICKS(100)); // delay for CPU saving
}

/** playing audio task */
void Task1(void *parameter) {
  for(;;) {
    player.loop();
    vTaskDelay(pdMS_TO_TICKS(1)); // giving chance to other task to run
  }
}

/** recording task */
void Task2(void *parameter) {
  for(;;) {
    if (touchSensor.isTouched()) {
      // recorder.record();
      // if (recorder.getLastSavedFileName() != "") {
      //   Serial.println(recorder.getLastSavedFileName().c_str());
      // }
      player.stop();
      delay(1000);
      player.play("/elevenlabs-sample-1.mp3");
    }
    // recorder.handleRecording();
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}

/** servo task */
void Task3(void *parameter) {
  for(;;) {
    // robot.walkForward();
    // if (ultrasonic.measureDistance() < 10) {
    //   robot.stop();
    //   delay(3000);
    //   robot.walkBackward();
    //   delay(500);
    //   robot.turnLeft();
    //   delay(1000);
    //   robot.walkForward();
    // }
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}