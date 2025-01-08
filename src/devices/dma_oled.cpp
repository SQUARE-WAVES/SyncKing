#include "dma_oled.h"
#include "daisy_seed.h"
#include "font.h"
#include <cstring>

using namespace daisy;
using namespace daisy::seed;

using namespace daisy;
using namespace daisy::seed;

//the buffer has to be a little big to accomodate the control byte
uint8_t DMA_BUFFER_MEM_SECTION screen_buffer[513];

void dma_end_cb(void* ctx,I2CHandle::Result result)
{
  auto dev = static_cast<dma_oled*>(ctx);
  dev->transfer_state = 0;
}

void dma_oled::init_hw()
{
  I2CHandle::Config i2c_conf;
  i2c_conf.periph = I2CHandle::Config::Peripheral::I2C_1;
  i2c_conf.speed = I2CHandle::Config::Speed::I2C_1MHZ;
  i2c_conf.mode = I2CHandle::Config::Mode::I2C_MASTER;
  i2c_conf.pin_config.scl = D11;
  i2c_conf.pin_config.sda = D12;
  i2c.Init(i2c_conf);
}

void dma_oled::send_cmd(uint8_t cmd)
{
  uint8_t buff[2] = {0x00, cmd};
  i2c.TransmitBlocking(screen_addr,buff,2,1000);
}

void dma_oled::init_screen()
{
  memset(screen_buffer,0x00,513);
  screen_buffer[0]=0xC0;

  memset(back_buffer,0x00,512);
  clear();

  send_cmd(0xAE); //DISPOFF

  send_cmd(0xD5); //CLKDIV_RATIO
  send_cmd(0x80); //figure this out?
 
  //multiplex ratio
  send_cmd(0xA8);
  send_cmd(0x3F);//hmmmmm

  //com pins stuff
  send_cmd(0xDA);
  send_cmd(0x00);

  // Display Offset
  send_cmd(0xD3);
  send_cmd(0x00);
  // Start Line Address
  send_cmd(0x40);
  //set to horizontal address mode
  send_cmd(0x20);
  send_cmd(0x00);

  //set up start and end pointers
  //to cover the whole screen
  //so we can update the whole thing at once
  //with DMA
  send_cmd(0x21);
  send_cmd(0x00);
  send_cmd(0x7F);

  //page start and end here
  send_cmd(0x22);
  send_cmd(0x04);
  send_cmd(0x07);

  // Normal Display
  send_cmd(0xA6);
  // All On Resume
  send_cmd(0xA4);
  // Charge Pump
  send_cmd(0x8D);
  send_cmd(0x14);
  // Set Segment Remap
  send_cmd(0xA1);
  // COM Output Scan Direction
  send_cmd(0xC8);
  // Contrast Control
  send_cmd(0x81);
  send_cmd(0xCF);
  // Pre Charge
  send_cmd(0xD9);
  send_cmd(0x1F);
  // VCOM Detect
  send_cmd(0xDB);
  send_cmd(0x40);

  // Display On
  send_cmd(0xAF); //--turn on oled panel
}

//writes the buffer to the screen
bool dma_oled::update()
{
  if(transfer_state != 0)
  {
    return false;
  }

  screen_buffer[0] = 0x40;

  memcpy(screen_buffer+1,back_buffer,screen_size);
  
  i2c.TransmitDma(screen_addr,screen_buffer,513,dma_end_cb,(void*)this);
  transfer_state = 1;
  return true;
}

void dma_oled::clear()
{
  memset(back_buffer,0x00,screen_size);
}

void dma_oled::draw_byte(size_t row,size_t col,uint8_t bits) {
  if ((row < 4) && (col < 128)) {
    size_t pos = row*128 + col;
    back_buffer[pos] = bits;
  }
}

void dma_oled::clear_line(size_t start)
{
  if(start > 4)
  {
    return;
  }

  size_t offset = 128 * start;
  memset(back_buffer + offset,0x00,width);
}

void dma_oled::write_ln(size_t lpad,size_t row,const char* str)
{
  size_t pos= (8*lpad) + (16*8*row);

  for(size_t i=0; i+lpad <16 && str[i] != 0; ++i)
  {
    const uint8_t* glyph = ascii_to_glyph(str[i]);
    memcpy(back_buffer + pos,glyph,8);
    pos += 8;
  }
}

void dma_oled::write_nm(size_t lpad, size_t row, int num)
{
  std::snprintf(strbuff,17,"%d",num);
  write_ln(lpad,row,strbuff);
}
