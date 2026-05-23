// module: tm.ko
// function: greg_get_mci_int_mask @ 0x321e8
// size: 192 bytes
//

undefined4
greg_get_mci_int_mask(uint param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (4 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_get_mci_int_mask] input invalid parameter:intrno=%d!\n",param_1);
    return 1;
  }
  iVar1 = tmOnuRegRead(param_1 + 0xe & 0xff,param_2,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    if (g_tm_debug_level == 0) {
      return 0;
    }
    printk("[TM][greg_get_mci_int_mask] output *pMask= %d!\n",*param_2);
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_get_mci_int_mask] greg_read_reg failed,ret= %d!\n",iVar1);
  return 0xffffffff;
}

