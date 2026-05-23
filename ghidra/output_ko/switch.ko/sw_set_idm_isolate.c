// module: switch.ko
// function: sw_set_idm_isolate @ 0x1306c
// size: 100 bytes
//

void sw_set_idm_isolate(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_r2;
  
  uVar1 = fpga_read_reg(0xe20f6);
  if (param_1 == 0) {
    if (param_2 == 1) {
      uVar1 = uVar1 & 0xffffffbf;
    }
    else {
      uVar1 = uVar1 | 0x40;
    }
  }
  else if (param_1 == 1) {
    if (param_2 == 1) {
      uVar1 = uVar1 & 0xffffff7f;
    }
    else {
      uVar1 = uVar1 | 0x80;
    }
    fpga_write_reg(0xe20f6,uVar1,extraout_r2,param_4);
    return;
  }
  fpga_write_reg(0xe20f6,uVar1,extraout_r2,param_4);
  return;
}

