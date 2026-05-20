// module: tm.ko
// function: greg_set_ptp_int_mask @ 0x3206c
// size: 92 bytes
//

undefined4
greg_set_ptp_int_mask(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = tmOnuRegWrite(0xd,param_1,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("greg_set_ptp_int_mask] GREG_WRITE_REG( failed,ret= %d!\n");
  return 0xffffffff;
}

