#include "io_port.h"
#include "../globals.h"

using namespace daisy;
using namespace daisy::seed;

void io_port::init(uint8_t addr)
{
  mcp.init_hw(addr);
  mcp.setup_registers();
  set_lights(0x00);
}

button_events io_port::poll()
{
  uint8_t new_state = mcp.read_port_b();
  uint8_t old_state = btns;

  btns = new_state;
  return button_events(old_state,new_state);
}

void io_port::set_lights(uint8_t sets)
{
  lts |= sets;
  blinkers &= ~sets;
}

void io_port::clear_lights(uint8_t clrs)
{
  lts &= ~clrs;
  blinkers &= ~clrs;
}

void io_port::blink_lights(uint8_t blinks)
{
  blinkers |= blinks;
}

void io_port::update_lights()
{
  lts ^= blinkers;
  mcp.set_port_a(lts);
}

//========================
button_events::button_events(uint8_t o,uint8_t n):old_st(o),new_st(n){}

int button_events::get(int n)
{
  int last = (old_st >> n) & 0x01;
  int current = (new_st >> n) & 0x01;

  return current-last;
}


