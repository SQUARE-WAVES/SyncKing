#include "ioexp.h"
#include "daisy_seed.h"

using namespace daisy;
using namespace daisy::seed;

const uint8_t TIMEOUT = 10;

const uint8_t IODIR_A = 0x00;
const uint8_t IODIR_B = 0x01;
const uint8_t IPOL_A = 0x02;
const uint8_t IPOL_B = 0x03;
const uint8_t GPINTEN_A = 0x04;
const uint8_t GPINTEN_B = 0x05;
const uint8_t DEFVAL_A = 0x06;
const uint8_t DEFVAL_B = 0x07;
const uint8_t INTCON_A = 0x08;
const uint8_t INTCON_B = 0x09;
const uint8_t IOCON  = 0x0A;
const uint8_t GPPU_A = 0x0C;
const uint8_t GPPU_B = 0x0D;
const uint8_t INTF_A = 0x0E;
const uint8_t INTF_B = 0x0F;
const uint8_t INTCAP_A = 0x10;
const uint8_t INTCAP_B = 0x11;
const uint8_t GPIO_A = 0x12;
const uint8_t GPIO_B = 0x13;
const uint8_t OLAT_A = 0x14;
const uint8_t OLAT_B = 0x15;

void ioexp::write_reg(uint8_t reg,uint8_t val)
{
  i2c.WriteDataAtAddress(i2c_addr,reg,1,&val,1,TIMEOUT);
}

void ioexp::write_reg(uint8_t reg,uint8_t val1, uint8_t val2)
{
  uint8_t buff[2] = {val1,val2};
  i2c.WriteDataAtAddress(i2c_addr,reg,1,buff,2,TIMEOUT);
}

uint8_t ioexp::read_reg(uint8_t reg) {
  uint8_t val = 0x00;
  i2c.ReadDataAtAddress(i2c_addr,reg,1,&val,1,TIMEOUT);
  return val;
}

void ioexp::init_hw(uint8_t addr)
{
  i2c_addr = addr;
  
  I2CHandle::Config i2c_conf;
  i2c_conf.periph = I2CHandle::Config::Peripheral::I2C_1;
  i2c_conf.speed = I2CHandle::Config::Speed::I2C_1MHZ;
  i2c_conf.mode = I2CHandle::Config::Mode::I2C_MASTER;
  i2c_conf.pin_config.scl = D11;
  i2c_conf.pin_config.sda = D12;
  i2c.Init(i2c_conf);
}

void ioexp::setup_registers()
{
  //bank in sequetial mode
  write_reg(IOCON,0b00100000);

  //port a output port b input 
  write_reg(IODIR_A,0x00,0xFF);
  //pull ups all around
  write_reg(GPPU_A,0xFF,0xFF);
  //port b reverse polarity
  write_reg(IPOL_A,0x00,0xFF);
}

void ioexp::set_port_a(uint8_t val) {
  write_reg(OLAT_A,val);
}

void ioexp::set_port_b(uint8_t val) {
  write_reg(OLAT_B,val);
}

void ioexp::set_ports(uint8_t a_val,uint8_t b_val) {
  write_reg(OLAT_A,a_val,b_val);
}

uint8_t ioexp::read_port_a() {
  return read_reg(GPIO_A);
}

uint8_t ioexp::read_port_b() {
  return read_reg(GPIO_B);
}

uint16_t ioexp::read_ports() {
  uint8_t vals[2] = {0x00,0x00};
  i2c.ReadDataAtAddress(i2c_addr,GPIO_A,1,vals,2,TIMEOUT);
  uint16_t out = vals[0];
  return out<<8 | vals[1];
}
