// module: bspdriver.ko
// function: init_module @ 0x10980
// size: 24 bytes
//

void init_module(void)

{
  printk("generic_i2c_init\n");
  i2c_setup();
  return;
}

