#include "Mic.h"
#include <driver/i2s.h>

void Mic::setup() {
  // Set up I2S Processor configuration
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 10,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false
  };

  // Install I2S driver
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);

  // Set I2S pin configuration
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_start(I2S_PORT);
}

int16_t Mic::read() {
  int16_t sample_buffer[BUFFER_SIZE];
  size_t bytes_read = 0;
  
  esp_err_t result = i2s_read(I2S_PORT, &sample_buffer, BUFFER_SIZE, &bytes_read, portMAX_DELAY);
  if (result == ESP_OK) {
    return sample_buffer[0]; // Return first sample from buffer
  }
  return 0;
}