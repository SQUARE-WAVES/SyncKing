#include "ui.h"
#include "../globals.h"

const char* sync_screen::title = "SYNC";

int sync_screen::knob_turn(int knob,int dir)
{
  switch (knob)
  {
    case 2:
    {
      loops.bump_bpm(dir);
      dirty = true;
    }
    break;
    case 3:
    {
      loops.bump_div(dir);
      dirty = true;
    }
    break;
    default:
    break;
  }

  return 0;
}

int sync_screen::knob_click(int knob)
{
  switch (knob)
  {
    case 2:
    {
      if(loops.going())
      {
        loops.stop();
        midi.send_stop();
      }
      else
      {
        loops.start();
        midi.send_start();
      }

      dirty = true;
    }
    break;
    case 3:
    {
      dirty=true;
      return 1;
    }
    break;
    default:
    break;
  }

  return 0;
}

void sync_screen::update()
{
  if(!dirty)
  {
    return;
  }

  oled.clear();
  oled.write_ln(6,0,title);
  oled.write_ln(0,1,"----------------");
  oled.write_ln(0,2,"BPM:");
  oled.write_nm(4,2,loops.bpm());

  oled.write_ln(8,2,"ON:");
  oled.write_ln(11,2,loops.going()?"-X-":"-0-");

  oled.write_ln(0,3,"DIV:");
  oled.write_ln(4,3,loops.sync_div());

  oled.update();
  dirty = false;
}

