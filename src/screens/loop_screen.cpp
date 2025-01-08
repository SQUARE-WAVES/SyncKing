#include "ui.h"
#include "../globals.h"

const char* loop_screen::title = "LOOP";

int loop_screen::knob_turn(int knob,int dir)
{
  switch (knob)
  {
    case 0:
    {
      loops.bump_loop_vol(num,dir);
      dirty = true;
    }
    break;
    case 1:
    {
      loops.bump_loop_pan(num,dir);
      dirty = true;
    }
    break;
    case 2:
    {
      loops.bump_loop_len(num,dir);
      dirty = true;
    }
    break;
    case 3:
    {
      num += dir;
      num = num % 4;
      dirty = true;
    }
    break;
    default:
    break;
  }

  return 1;
}

int loop_screen::knob_click(int knob)
{
  if(knob == 3)
  {
    dirty = true;
    return 0;
  }
  else
  {
    return 1;
  }
}

void loop_screen::update()
{
  if(!dirty)
  {
    return;
  }

  oled.clear();
  oled.write_ln(4,0,title);
  oled.write_nm(10,0,num+1);
  oled.write_ln(0,1,"----------------");
  
  oled.write_ln(0,2,"LEN:");
  oled.write_ln(4,2,loops.get_loop_len(num));

  oled.write_ln(0,3,"VOL:");
  float v = loops.get_loop_vol(num) * 100.0;
  oled.write_nm(4,3,static_cast<int>(v));

  oled.write_ln(8,3,"PAN:");
  float p = loops.get_loop_pan(num) * 100.0;
  oled.write_nm(12,3,static_cast<int>(p));
  
  oled.update();
  dirty = false;
}

