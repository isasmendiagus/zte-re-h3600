// module: bspdriver.ko
// function: hw_power_optx_get_fordg @ 0x10950
// size: 48 bytes
//

void hw_power_optx_get_fordg(void)

{
  bob_i2c_readb(0x51,0x6e,&txdisable);
  printk("hw_power_optx_get_fordg:txdisable=%x\n",txdisable);
  return;
}

