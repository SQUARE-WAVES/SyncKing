#include "daisy_seed.h"
#include "globals.h"

using namespace daisy;
using namespace daisy::seed;

DaisySeed hw;
io_port prt;
io_port prt2;

dma_oled oled;
midi_guy midi;

encoder code1;
encoder code2;
encoder code3;
encoder code4;

screen_set screen;

//this is enough for 4 stereo loops of up to 8 bars at 60 bpm
//2000 samples per timing pulse 96 pulses per bar, 8 bars, 8 tracks (4l 4r)
float DSY_SDRAM_BSS big_buff[2000 * 96 * 8 * 8]; 
looper loops(big_buff);

void init_globals()
{
  hw.Configure();
  hw.Init();
  hw.StartLog();

  prt.init(0x20<<1);
  prt2.init(0x24<<1);

  code1.init(D0,D4,D5);
  code2.init(D1,D6,D7);
  code3.init(D2,D26,D27);
  code4.init(D3,D30,D29);

  oled.init_hw();
  oled.init_screen();
  oled.update();

  midi.init();
  
  memset(big_buff,0x00,sizeof(big_buff));
}
