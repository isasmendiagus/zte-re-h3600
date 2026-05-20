// module: mt7915.ko
// function: AsicSetRxvFilter @ 0x13405c
// size: 136 bytes
//

int AsicSetRxvFilter(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xdc) == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicSetRxvFilter");
    return 0;
  }
  iVar1 = (**(code **)(iVar1 + 0xdc))(param_1,param_2,param_3);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s(): SetRxvTxRx failed!\n","AsicSetRxvFilter");
    return iVar1;
  }
  return iVar1;
}

