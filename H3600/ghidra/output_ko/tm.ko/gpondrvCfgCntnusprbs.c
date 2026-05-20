// module: tm.ko
// function: gpondrvCfgCntnusprbs @ 0x63d5c
// size: 108 bytes
//

void gpondrvCfgCntnusprbs(int param_1)

{
  int iVar1;
  
  iVar1 = fpga_read_reg(0x10006);
  if (iVar1 != 0) {
    printk("error:not gpon mode\n");
    return;
  }
  fpga_read_reg(0x36000);
  if (param_1 == 0) {
    serdes_set_gen_en_disable();
    fpga_write_reg(0x36000,0);
    return;
  }
  fpga_write_reg(0x36000,1);
  serdes_set_tx_prbs_mode(param_1 + -1);
  serdes_set_gen_en_open();
  return;
}

