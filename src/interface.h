#pragma once

class screen_set
{
  //this is dumb but I'll fix it later
  int current_screen = 0;

  public:
  void knob_turn(int knob,int dir);
  void knob_click(int knob);

  void update();
};
