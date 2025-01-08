#pragma once

class bpm_param
{
  static const int min = 60;
  static const int max = 240;

  int val = 120;

  public:
  size_t bump(int amt);
  size_t get_timing();
  int get_val() {return val;}
};


class div_param
{
  static const int min = 0;
  static const int max = 10;

  int val = 3;

  public:
  size_t bump(int amt);
  size_t get_mod();
  const char* get_str();
};


/*
class vol_param
{
  static const int min = 0;
  static const int max = 100;

  uint8_t val = 100;

  public:
  void bump(int amt);
  float get_val();
  const char* get_str();
};
class pan_param
{
  static const int min = 0;
  static const int max = 100;

  int val = 100;

  public:
  void bump(int amt);
  float get_val();
  char[3] get_str();
};
*/
