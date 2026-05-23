// module: tm.ko
// function: greg_set_mci_int_mask @ 0x3214c
// size: 156 bytes
//

undefined4
greg_set_mci_int_mask(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (4 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_set_mci_int_mask] input invalid parameteintrno=%d!\n",param_1);
    return 1;
  }
  iVar1 = tmOnuRegWrite(param_1 + 0xe & 0xff,param_2,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("greg_set_int_mask GREG_WRITE_REG( failed,ret= %d!\n");
  return 0xffffffff;
}

