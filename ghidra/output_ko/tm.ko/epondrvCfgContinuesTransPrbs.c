// module: tm.ko
// function: epondrvCfgContinuesTransPrbs @ 0x613c4
// size: 136 bytes
//

undefined4 epondrvCfgContinuesTransPrbs(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = fpga_read_reg(0x10006);
  if (iVar1 != 1) {
    printk("error:not epon mode\n");
    return 0xffffffff;
  }
  uVar2 = fpga_read_reg(0x2000d);
  if (param_1 == 0) {
    serdes_set_gen_en_disable();
    fpga_write_reg(0x2000d,uVar2 & 0x7fffffff);
    return 0;
  }
  fpga_write_reg(0x2000d,uVar2 | 0x80000000);
  serdes_set_tx_prbs_mode(param_1 + -1);
  serdes_set_gen_en_open();
  return 0;
}

