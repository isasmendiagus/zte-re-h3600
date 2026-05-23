// module: switch.ko
// function: sw_reg_set_readreg @ 0x1a074
// size: 272 bytes
//

undefined4 sw_reg_set_readreg(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_1[1];
  if (g_switch_debug_level < 3) {
    uVar1 = fpga_read_reg(*param_1);
  }
  else {
    printk("[%s] input:\n%s = 0x%x\n","sw_reg_set_readreg","Reg.addr");
    uVar1 = fpga_read_reg(*param_1);
  }
  uVar2 = g_switch_debug_level;
  param_1[2] = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
               uVar1 >> 0x18;
  if (uVar2 < 3) {
    if (uVar3 == 0) {
      return 0;
    }
  }
  else {
    printk("[%s] output:\nReg.value = 0x","sw_reg_set_readreg");
    uVar2 = g_switch_debug_level;
    if (uVar3 == 0) goto LAB_0001a0fc;
  }
  param_1 = param_1 + 2;
  uVar1 = 0;
  do {
    uVar1 = uVar1 + 1;
    if (2 < uVar2) {
      printk("%02x ",*(undefined1 *)param_1);
      uVar2 = g_switch_debug_level;
    }
    param_1 = (undefined4 *)((int)param_1 + 1);
  } while (uVar1 < uVar3);
LAB_0001a0fc:
  if (2 < uVar2) {
    printk(&_LC4);
  }
  return 0;
}

