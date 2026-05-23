// module: tm.ko
// function: greg_get_soam_int_mask @ 0x31fe8
// size: 132 bytes
//

undefined4
greg_get_soam_int_mask(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = tmOnuRegRead(0xc,param_1,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    if (g_tm_debug_level == 0) {
      return 0;
    }
    printk("[TM][greg_get_soam_int_mask] output *pMask= %d!\n",*param_1);
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_get_soam_int_mask] greg_read_reg failed,ret= %d!\n",iVar1);
  return 0xffffffff;
}

