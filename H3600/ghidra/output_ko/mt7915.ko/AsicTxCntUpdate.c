// module: mt7915.ko
// function: AsicTxCntUpdate @ 0x13320c
// size: 176 bytes
//

void AsicTxCntUpdate(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x60) == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicTxCntUpdate");
    return;
  }
  (**(code **)(iVar1 + 0x60))(param_1,param_2,param_3);
  iVar1 = param_3[1];
  iVar3 = *param_3;
  if (iVar1 == 0) {
    *(int *)(param_1 + 0xa39e20) = *(int *)(param_1 + 0xa39e20) + iVar3;
  }
  else {
    *(int *)(param_1 + 0xa39e24) = *(int *)(param_1 + 0xa39e24) + iVar3;
  }
  iVar2 = param_3[1];
  *(int *)(param_1 + 0xa39c00) = (iVar3 + *(int *)(param_1 + 0xa39c00)) - iVar1;
  *(int *)(param_1 + 0xa39e1c) = iVar2 + *(int *)(param_1 + 0xa39e1c);
  *(int *)(param_1 + 0xa39c10) = param_3[1] + *(int *)(param_1 + 0xa39c10);
  return;
}

