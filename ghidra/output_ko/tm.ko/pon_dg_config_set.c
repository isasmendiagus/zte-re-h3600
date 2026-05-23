// module: tm.ko
// function: pon_dg_config_set @ 0x4f0dc
// size: 44 bytes
//

undefined4 pon_dg_config_set(int param_1,int param_2,int param_3,int param_4,uint param_5)

{
  uint uVar1;
  
  param_5 = param_5 | param_4 << 1;
  uVar1 = param_5 | param_3 << 0xf;
  fpga_write_reg(0x10009,uVar1 | param_2 << 0x10 | param_1 << 0x11,uVar1,param_5,param_4);
  return 0;
}

