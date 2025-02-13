#include <Arduino.h>
#include "TouchSensor.h"
#include "AudioRecorder.h"
#include "AudioPlayer.h"
#include "Robot.h"
#include "Ultrasonic.h"
#include "Http.h"

SDCard* sdCard;
TouchSensor touchSensor;
AudioRecorder recorder;
AudioPlayer player;
Robot robot;
Ultrasonic ultrasonic;
Http http;

// task declaration
void AudioPlayerTask(void *parameter);
void AudioRecorderTask(void *parameter);
void ServoTask(void *parameter);

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
    AudioPlayerTask,    // task function
    "AudioPlayerTask",  // task name
    10000,    // stack size
    NULL,     // parameter
    1,        // priority
    NULL      // task handle
  );

  xTaskCreate(
    AudioRecorderTask,
    "AudioRecorderTask",
    10000,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    ServoTask,
    "ServoTask",
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

void AudioPlayerTask(void *parameter) {
  for(;;) {
    player.loop();
    vTaskDelay(pdMS_TO_TICKS(1)); // giving chance to other task to run
  }
}

void AudioRecorderTask(void *parameter) {
  for(;;) {
    if (touchSensor.isTouched()) {
      recorder.record();
      if (recorder.getLastSavedFileName() != "") {
        String fileName = recorder.getLastSavedFileName().c_str();
        Serial.println(fileName.c_str());        
        File file = SD.open(fileName, FILE_READ);
        if (file) {
          size_t fileSize = file.size();
          uint8_t* buffer = (uint8_t*)malloc(fileSize);
          if (buffer) {
            file.read(buffer, fileSize);
            file.close();
            
            // Send the binary data and save response
            String url = "http://192.168.207.213:3000/api/speech-to-speech/generate?key=gadingnst";
            String outputFile = "/response.mp3";
            if (http.postBinary(url, buffer, fileSize, outputFile, "Content-Type: audio/wav")) {
              // Play the response audio
              player.play(outputFile.c_str());
            }
            free(buffer);
          }
        }
      }
    }
    recorder.handleRecording();
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}

void ServoTask(void *parameter) {
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