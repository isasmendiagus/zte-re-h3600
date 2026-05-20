// module: bspdriver.ko
// function: plat_i2c_write_byte @ 0x1033c
// size: 8 bytes
//

void plat_i2c_write_byte(uint param_1)

{
  i2c_writeb(param_1 >> 1);
  return;
}

