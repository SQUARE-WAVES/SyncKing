#pragma once

class screen_handler
{
  public:
  virtual int knob_turn(int knob,int dir) =0;
  virtual int knob_click(int knob) =0;
  virtual void update() = 0;
};

//==============================================================================
// These all need to be in this file so we do less includes when building
// the full ui

class loop_screen : public screen_handler
{
  static const char* title; 
  bool dirty = true;
  size_t num = 0;

  public:
  int knob_turn(int knob,int dir) override;
  int knob_click(int knob) override;
  void update() override;
};

class sync_screen : public screen_handler
{
  static const char* title; 
  bool dirty = true;

  public:
  int knob_turn(int knob,int dir) override;
  int knob_click(int knob) override;
  void update() override;
};
