// module: tm.ko
// function: greg_set_ptp_int_req @ 0x31bf4
// size: 148 bytes
//

undefined4
greg_set_ptp_int_req(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_set_ptp_int_req] input invalid parameter,en=%d!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(1,param_1,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("greg_set_ptp_int_req] GREG_WRITE_REG( failed,ret= %d!\n");
  return 0xffffffff;
}

