// module: switch.ko
// function: sw_reg_set_writereg @ 0x1a184
// size: 228 bytes
//

undefined4 sw_reg_set_writereg(undefined4 *param_1)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar3 = param_1 + 2;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = 0x%x\n","sw_reg_set_writereg","Reg.addr",*param_1);
    if (2 < g_switch_debug_level) {
      printk("Reg.value = 0x");
    }
  }
  uVar1 = g_switch_debug_level;
  puVar2 = puVar3;
  do {
    if (2 < uVar1) {
      printk("%02x ",(char)*puVar2);
      uVar1 = g_switch_debug_level;
    }
    puVar2 = (uint *)((int)puVar2 + 1);
  } while (puVar2 != param_1 + 3);
  if (uVar1 < 3) {
    uVar1 = *puVar3;
  }
  else {
    printk(&_LC4);
    uVar1 = *puVar3;
  }
  fpga_write_reg(*param_1,uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8
                          | uVar1 >> 0x18);
  return 0;
}

