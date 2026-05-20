// module: mt7915.ko
// function: Set_TxRate_Proc @ 0x377a8
// size: 96 bytes
//

undefined4 Set_TxRate_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  __memzero("\n" + (int)(param_1 + *(int *)(iVar2 + 0x3c) * 0x160d),0xc,param_3,
            param_1 + *(int *)(iVar2 + 0x3c) * 0x160d,param_4);
  iVar2 = *(int *)(iVar2 + 0x3c);
  uVar1 = os_str_tol(param_2,0,10);
  *(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2bb615) = uVar1;
  return 1;
}

