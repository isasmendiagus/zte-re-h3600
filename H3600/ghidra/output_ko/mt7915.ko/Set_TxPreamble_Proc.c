// module: mt7915.ko
// function: Set_TxPreamble_Proc @ 0xd9c64
// size: 204 bytes
//

undefined4 Set_TxPreamble_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  
  iVar2 = os_str_tol(param_2,0,10,param_4,param_4);
  cVar1 = *(char *)(param_1 + 0x286285);
  if (iVar2 == 2 && cVar1 == '\x01') {
    return 0;
  }
  if (iVar2 == 1) {
    *(undefined4 *)(param_1 + 0x795064) = 1;
    if (cVar1 == '\0') {
      MlmeSetTxPreamble(param_1,1);
    }
  }
  else {
    if ((iVar2 != 0) && (iVar2 != 2)) {
      return 0;
    }
    *(int *)(param_1 + 0x795064) = iVar2;
    if (cVar1 == '\0') {
      MlmeSetTxPreamble(param_1);
    }
  }
  if (2 < DebugLevel) {
    printk("Set_TxPreamble_Proc::(TxPreamble=%ld)\n",*(undefined4 *)(param_1 + 0x795064));
    return 1;
  }
  return 1;
}

