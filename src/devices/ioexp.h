#pragma once

#include "daisy_seed.h"

class ioexp {
  uint8_t i2c_addr;
  daisy::I2CHandle i2c;

  void write_reg(uint8_t reg,uint8_t val);
  void write_reg(uint8_t reg,uint8_t val1, uint8_t val2);

  uint8_t read_reg(uint8_t reg);

  public:
  void init_hw(uint8_t addr);
  void setup_registers();
  void set_port_a(uint8_t val);
  void set_port_b(uint8_t val);
  void set_ports(uint8_t a_val,uint8_t b_val);

  uint8_t read_port_a();
  uint8_t read_port_b();
  uint16_t read_ports();
};
