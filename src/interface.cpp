#include "globals.h"
#include "screens/ui.h"

//this is dumb but I'll figure it out later
screen_handler& get_screen(int scr)
{
  static loop_screen loop_scr;
  static sync_screen sync_scr;

  switch(scr)
  {
    case 1: 
      return loop_scr;
    break;

    default:
      return sync_scr;
    break;
  }
}

void screen_set::knob_turn(int knob, int dir)
{
  screen_handler& h = get_screen(current_screen);
  current_screen = h.knob_turn(knob,dir);
}

void screen_set::knob_click(int knob)
{
  screen_handler& h = get_screen(current_screen);
  current_screen = h.knob_click(knob);
}

void screen_set::update()
{
  screen_handler& h = get_screen(current_screen);
  h.update();
}
