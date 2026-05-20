// module: tm.ko
// function: tm_set_pp_wan_cfg @ 0x46464
// size: 92 bytes
//

void tm_set_pp_wan_cfg(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = fpga_read_reg(0xe8007);
  printk("PON_PP_TM_CFG=0x%x\n",uVar1);
  fpga_write_reg(0xe8007,uVar1 | 1 << (param_1 + 0x19U & 0xff));
  uVar2 = fpga_read_reg(0xe8007);
  printk("after PON_PP_TM_CFG=0x%x\n",uVar2);
  return;
}

