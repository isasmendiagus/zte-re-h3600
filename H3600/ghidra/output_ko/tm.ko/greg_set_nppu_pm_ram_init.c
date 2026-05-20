// module: tm.ko
// function: greg_set_nppu_pm_ram_init @ 0x32654
// size: 148 bytes
//

undefined4
greg_set_nppu_pm_ram_init(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x1f < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_set_nppu_pm_ram_init] input invalid parameter,control = %d!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x1c,param_1,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_set_nppu_pm_ram_init] GREG_WRITE_REG( failed,ret= %d!\n");
  return 0xffffffff;
}

