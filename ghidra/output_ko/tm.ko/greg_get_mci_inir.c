// module: tm.ko
// function: greg_get_mci_inir @ 0x31da8
// size: 172 bytes
//

undefined4 greg_get_mci_inir(uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == 0 || 4 < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][greg_get_mci_inir] input invalid parameter,intrno = %d!\n",param_1);
      return 1;
    }
    return 1;
  }
  iVar1 = tmOnuRegRead(param_1 + 2 & 0xff,param_2,0,&gregRegTable,param_4);
  if (iVar1 != 0) {
    if (g_tm_debug_level != 0) {
      printk("greg_get_mci_inir] greg_read_reg failed,ret= %d!\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  return 0;
}

