// module: bspdriver.ko
// function: plat_i2c_read_byte @ 0x10678
// size: 8 bytes
//

void plat_i2c_read_byte(uint param_1)

{
  i2c_readb(param_1 >> 1);
  return;
}

