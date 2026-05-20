// module: bspdriver.ko
// function: plat_i2c_probe @ 0x10668
// size: 16 bytes
//

void plat_i2c_probe(uint param_1)

{
  bsp_i2c_probe(param_1 >> 1,0,0);
  return;
}

