// module: mt7915.ko
// function: AsicSetMacTxRx @ 0x133f88
// size: 208 bytes
//

int AsicSetMacTxRx(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xd8) == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicSetMacTxRx");
    return 0;
  }
  iVar2 = (**(code **)(iVar1 + 0xd8))(param_1,param_2,param_3,0);
  if ((iVar2 == 0) &&
     ((*(char *)(param_1 + 0x79504d) == '\0' ||
      (iVar2 = (**(code **)(iVar1 + 0xd8))(param_1,param_2,param_3,1), iVar2 == 0)))) {
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s(): SetMacTxRx failed!\n","AsicSetMacTxRx");
    return iVar2;
  }
  return iVar2;
}

