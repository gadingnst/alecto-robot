#include <Arduino.h>
#include "TouchSensor.h"
#include "AudioRecorder.h"
#include "AudioPlayer.h"
#include "Display.h"

SDCard* sdCard;
TouchSensor touchSensor;
Display display;
AudioPlayer player;
AudioRecorder recorder;

// Define task handles
TaskHandle_t displayTaskHandle;
TaskHandle_t audioTaskHandle;

// Display task function
void displayTask(void *parameter) {
  for(;;) {
    display.idle();
    vTaskDelay(1); // Allow other tasks to run
  }
}

// Audio task function
void audioTask(void *parameter) {
  for(;;) {
    player.loop();
    vTaskDelay(1);
  }
}

void setup() {
  Serial.begin(115200);
  sdCard = new SDCard();
  sdCard->setup();
  display.setup();
  touchSensor.setup();
  player.setup(sdCard);
  recorder.setup(sdCard);
  
  // Create tasks on different cores
  xTaskCreatePinnedToCore(
    displayTask,    // Task function
    "DisplayTask",  // Name
    8192,          // Stack size (increased from 4096)
    NULL,          // Parameters
    2,             // Priority (increased from 1)
    &displayTaskHandle,    // Task handle
    0              // Core 0
  );
  
  xTaskCreatePinnedToCore(
    audioTask,     // Task function
    "AudioTask",   // Name
    4096,          // Stack size
    NULL,          // Parameters
    1,             // Priority
    &audioTaskHandle,     // Task handle
    1              // Core 1
  );

  Serial.println("Setup complete.");
  player.play("/elevenlabs.mp3");
}

void loop() {
  vTaskDelay(1);
  if (touchSensor.isTouched()) {
    Serial.println("Touched");
    delay(1000);
  }
} 