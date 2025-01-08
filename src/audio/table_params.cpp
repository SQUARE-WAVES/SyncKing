#include <algorithm>
#include "table_params.h"

static const constexpr size_t timing_table[] = {
  2000,
  1967,
  1935,
  1904,
  1875,
  1846,
  1818,
  1791,
  1764,
  1739,
  1714,
  1690,
  1666,
  1643,
  1621,
  1600,
  1578,
  1558,
  1538,
  1518,
  1500,
  1481,
  1463,
  1445,
  1428,
  1411,
  1395,
  1379,
  1363,
  1348,
  1333,
  1318,
  1304,
  1290,
  1276,
  1263,
  1250,
  1237,
  1224,
  1212,
  1200,
  1188,
  1176,
  1165,
  1153,
  1142,
  1132,
  1121,
  1111,
  1100,
  1090,
  1081,
  1071,
  1061,
  1052,
  1043,
  1034,
  1025,
  1016,
  1008,
  1000,
  991,
  983,
  975,
  967,
  960,
  952,
  944,
  937,
  930,
  923,
  916,
  909,
  902,
  895,
  888,
  882,
  875,
  869,
  863,
  857,
  851,
  845,
  839,
  833,
  827,
  821,
  816,
  810,
  805,
  800,
  794,
  789,
  784,
  779,
  774,
  769,
  764,
  759,
  754,
  750,
  745,
  740,
  736,
  731,
  727,
  722,
  718,
  714,
  710,
  705,
  701,
  697,
  693,
  689,
  685,
  681,
  677,
  674,
  670,
  666,
  662,
  659,
  655,
  652,
  648,
  645,
  641,
  638,
  634,
  631,
  628,
  625,
  621,
  618,
  615,
  612,
  609,
  606,
  603,
  600,
  597,
  594,
  591,
  588,
  585,
  582,
  579,
  576,
  574,
  571,
  568,
  566,
  563,
  560,
  558,
  555,
  552,
  550,
  547,
  545,
  542,
  540,
  538,
  535,
  533,
  530,
  528,
  526,
  524,
  521,
  519,
  517,
  515,
  512,
  510,
  508,
  506,
  504,
  502,
  500
};

static const constexpr size_t mod_table[] = {
  12, //1/8
  24, //1/4
  48, //1/2
  96, //1 bar
  192, //2 bars
  288, //3 bars
  384, //4 bars
  480, //5 bars
  576, //6 bars
  672, //7 bars
  768, //8 bars
};

static const char* mod_str_table[] = {
  "1/8",
  "1/4",
  "1/2",
  "1 bar",
  "2 bars",
  "3 bars",
  "4 bars",
  "5 bars",
  "6 bars",
  "7 bars",
  "8 bars"
};

size_t bpm_param::get_timing()
{
  return timing_table[val-60];
}

size_t bpm_param::bump(int amt)
{
  int new_val = val + amt;

  if(new_val < min)
  {
    val = min;
    return get_timing();
  }
  else if(new_val > max)
  {
    val = max;
    return get_timing();
  }
  else
  {
    val = new_val;
    return get_timing();
  }
}

size_t div_param::get_mod()
{
  return mod_table[val];
}

const char* div_param::get_str()
{
  return mod_str_table[val];
}

size_t div_param::bump(int amt)
{
  int new_val = val + amt;

  if(new_val < min)
  {
    val = min;
    return get_mod();
  }
  else if(new_val > max)
  {
    val = max;
    return get_mod();
  }
  else
  {
    val = new_val;
    return get_mod();
  }
}
