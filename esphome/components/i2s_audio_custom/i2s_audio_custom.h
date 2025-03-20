#pragma once

#ifdef USE_ESP32

#include "esphome/components/i2s_audio/i2s_audio.h"
#include "esphome/components/microphone/microphone.h"
#include "esphome/core/component.h"
#include "esphome/core/ring_buffer.h"

namespace esphome {
namespace i2s_audio_custom {

class I2SAudioMicrophoneCustom : public i2s_audio::I2SAudioIn, public microphone::Microphone, public Component {
 public:
  void setup() override;
  void start() override;
  void stop() override;

  void loop() override;

  void set_din_pin(int8_t pin) { this->din_pin_ = pin; }
  void set_pdm(bool pdm) { this->pdm_ = pdm; }

  size_t read(int16_t *buf, size_t len) override;

#if SOC_I2S_SUPPORTS_ADC
  void set_adc_channel(adc1_channel_t channel) {
    this->adc_channel_ = channel;
    this->adc_ = true;
  }
#endif

 protected:
  void start_();
  void stop_();
  void read_();

  int8_t din_pin_{I2S_PIN_NO_CHANGE};
#if SOC_I2S_SUPPORTS_ADC
  adc1_channel_t adc_channel_{ADC1_CHANNEL_MAX};
  bool adc_{false};
#endif
  bool pdm_{false};

  HighFrequencyLoopRequester high_freq_;
};

}  // namespace i2s_audio
}  // namespace esphome

#endif  // USE_ESP32
