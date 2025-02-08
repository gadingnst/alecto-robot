#include "Mic.h"

Mic::Mic(MicType micType) {
  if (_isAlreadyInitialized) return;
  _micType = micType;
  _isAlreadyInitialized = true;
  if (micType == M5GO || micType == M5STACKFIRE) {
    _bitsPerSample = I2S_BITS_PER_SAMPLE_16BIT;
    i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_TX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = _bitsPerSample,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 2,
      .dma_buf_len = BUFFER_SIZE
    };
    i2s_pin_config_t pin_config;
    pin_config.bck_io_num = I2S_SCK;
    pin_config.ws_io_num = I2S_WS;
    pin_config.data_out_num = I2S_PIN_NO_CHANGE;
    pin_config.data_in_num = I2S_SD;
    pin_config.mck_io_num = I2S_PIN_NO_CHANGE;
    
    // Uninstall any existing driver before installing a new one
    i2s_driver_uninstall(I2S_PORT);
    
    // Install the I2S driver
    esp_err_t err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    if (err != ESP_OK) {
      Serial.println("Failed to install I2S driver");
      return;
    }
    
    // Set the I2S pins
    i2s_set_pin(I2S_PORT, &pin_config);
    i2s_set_clk(I2S_PORT, SAMPLE_RATE, _bitsPerSample, I2S_CHANNEL_STEREO);
  } else if (micType == ADMP441 || micType == ICS43434) {
    _bitsPerSample = I2S_BITS_PER_SAMPLE_32BIT;
    i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = _bitsPerSample,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 16,
      .dma_buf_len = 60
    };
    i2s_pin_config_t pin_config;
    pin_config.bck_io_num = I2S_SCK;
    pin_config.ws_io_num = I2S_WS;
    pin_config.data_out_num = I2S_PIN_NO_CHANGE;
    pin_config.data_in_num = I2S_SD;
    pin_config.mck_io_num = I2S_PIN_NO_CHANGE;
    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pin_config);
    i2s_set_clk(I2S_PORT, SAMPLE_RATE, _bitsPerSample, I2S_CHANNEL_STEREO);
  }
}

int Mic::read(char* data, int numData) {
  size_t bytesRead;
  esp_err_t result = i2s_read(I2S_PORT, data, numData, &bytesRead, portMAX_DELAY);
  if (result == ESP_OK) {
    return bytesRead;
  } else {
    return 0;
  }
}

int Mic::getBitsPerSample() {
  return (int)_bitsPerSample;
}
