#include "encoder.h"

using namespace daisy;

void encoder::init(Pin btn_pin,Pin dt_pin,Pin clk_pin)
{
  btn.Init(btn_pin,GPIO::Mode::INPUT,GPIO::Pull::PULLUP);
  dt.Init(dt_pin,GPIO::Mode::INPUT,GPIO::Pull::PULLUP);
  clk.Init(clk_pin,GPIO::Mode::INPUT,GPIO::Pull::PULLUP);
}

int encoder::poll()
{
  uint8_t clk_v = clk.Read() * 0x10;
  uint8_t dt_v = dt.Read() * 0x01;

  track = (((track << 1)) | clk_v | dt_v) & 0x33;

  //this is some branchless hacking, it's probably overkill
  //but this thing will get polled pretty "frequently"
  //if its 0x20 you will get -1 if its 0x02 you will get 1;
  return -1 * (((track==0x20) * -1) + (track==0x02));
}

int encoder::poll_btn()
{
  int nv = !btn.Read();
  int ov = btn_val;
  btn_val = nv;

  return ov - nv;
}
