#include "Speaker.h"

void Speaker::setup(SDCard* sdCard) {
  sd = sdCard;

  // Configure I2S
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = sampleRate,
    .bits_per_sample = bitsPerSample,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  // Configure I2S pins
  i2s_pin_config_t pin_config = {
    .mck_io_num = I2S_PIN_NO_CHANGE,
    .bck_io_num = BCLK_PIN,
    .ws_io_num = LRCLK_PIN,
    .data_out_num = DIN_PIN,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  // Install and start I2S driver
  i2s_driver_install(SPEAKER_I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(SPEAKER_I2S_PORT, &pin_config);
  i2s_start(SPEAKER_I2S_PORT);

  // Setup audio output
  out = new AudioOutputI2S(SPEAKER_I2S_PORT);  // Specify I2S port
  out->SetPinout(BCLK_PIN, LRCLK_PIN, DIN_PIN);
  out->SetRate(sampleRate);
  out->SetBitsPerSample(bitsPerSample);
  // out->SetGain(0.125);  // Adjust gain as needed
}

void Speaker::end() {
  if (out) {
    delete out;
    out = nullptr;
  }
  i2s_driver_uninstall(SPEAKER_I2S_PORT);
}

bool Speaker::playMP3File(const char* filename) {
  file = new AudioFileSourceSDMMC(filename, sd);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(file, out);

  while (mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
    }
  }

  delete file;
  delete mp3;
  return true;
}