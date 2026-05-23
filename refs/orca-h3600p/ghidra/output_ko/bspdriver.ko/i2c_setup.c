// module: bspdriver.ko
// function: i2c_setup @ 0x10700
// size: 88 bytes
//

undefined4 i2c_setup(void)

{
  int iVar1;
  
  pI2cDevs = &bosa_i2c_writeb;
  iVar1 = i2c_get_adapter(0);
  if (iVar1 != 0) {
    kfree(0x10);
    i2c_put_adapter(iVar1);
    return 0;
  }
  printk("can\'t get i2c adapter 0\n");
  kfree(0x10);
  return 0xffffffff;
}

