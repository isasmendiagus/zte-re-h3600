// module: tm.ko
// function: greg_set_smct_ram_init @ 0x3252c
// size: 148 bytes
//

undefined4
greg_set_smct_ram_init(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (3 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_set_smct_ram_init] input invalid parameter,control = %d!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x1a,param_1,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_set_smct_ram_init] GREG_WRITE_REG( failed,ret= %d!\n");
  return 0xffffffff;
}

