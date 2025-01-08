#pragma once
#include "daisy_seed.h"

void dma_end_cb(void* ctx,daisy::SpiHandle::Result result);
void dma_start_cb(void* ctx);

class dma_oled
{ 
  //commands
  static const uint8_t DISPOFF = 0xAE;
  static const uint8_t CLKDIV_RATIO = 0xD5;

  static const int width = 128;
  static const int height = 32;
  static const int screen_size = 512;

  uint16_t screen_addr = 0x3C;

  daisy::I2CHandle i2c;

  friend void dma_end_cb(void* ctx,daisy::I2CHandle::Result result);
  friend void dma_start_cb(void* ctx);

  //this is which buffer we are on
  int screen_start = 0;

  //ok the transfer state is basically "nothing is going on"
  //1 = we are waiting for a transfer to start so our buffer is not safe
  //2 = we are waiting for a transfer to end so we can't start a new one
  int transfer_state = 0;

  uint8_t back_buffer[screen_size];

  public:
  void init_hw();
  void init_screen();
  void send_cmd(uint8_t cmd);

  bool update();
  void clear();

  void draw_byte(size_t row,size_t col,uint8_t bits);
  inline bool available() { return transfer_state == 0; }

  //if you also have a glyph font
  char strbuff[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  void clear_line(size_t start);
  void write_ln(size_t lpad, size_t row, const char* str);
  void write_nm(size_t lpad, size_t row, int num);
};
