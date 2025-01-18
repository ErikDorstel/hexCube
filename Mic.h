#include <driver/i2s.h>

struct micStruct {
  int16_t mean; int16_t max; } mic;

void i2s_install_0() {
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 48000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 4,
    .dma_buf_len = 64,
    .use_apll = false };
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL); }

void i2s_setpin_0() {
  const i2s_pin_config_t pin_config = {
    .bck_io_num = 17,
    .ws_io_num = 18,
    .data_out_num = -1,
    .data_in_num = 16 };
  i2s_set_pin(I2S_NUM_0, &pin_config); }

void initMic() {
  i2s_install_0();
  i2s_setpin_0();
  i2s_start(I2S_NUM_0); }

void micWorker() {
  int16_t inBuffer[64]={0}; size_t bytesIn=0;
  int64_t sum=0; int16_t max=0;
  i2s_read(I2S_NUM_0, &inBuffer, 128, &bytesIn, portMAX_DELAY);
  for (uint16_t i=0;i<(bytesIn>>1);i++) { sum+=inBuffer[i]; if (inBuffer[i]>max) { max=inBuffer[i]; } }
  mic.mean=sum/(bytesIn>>1); mic.max=max; }
