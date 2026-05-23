// module: mt7915.ko
// function: vow_avg_pkt_len_calculate @ 0x4a1b0
// size: 96 bytes
//

void vow_avg_pkt_len_calculate(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(*(int *)(param_1 + 8) + 8);
  if (*(int *)(param_1 + 0x136c) == 0) {
    return;
  }
  iVar1 = __aeabi_uidiv(*(undefined4 *)(param_1 + 0x1360));
  if (0x7a8 < iVar1 - 0x28U) {
    return;
  }
  uVar3 = (uint)*(byte *)(iVar4 + 0xa7be3c);
  uVar2 = __aeabi_uidiv(*(int *)(iVar4 + 0xa7be38) * uVar3 + iVar1,uVar3 + 1,
                        *(int *)(iVar4 + 0xa7be38),uVar3,param_4);
  *(char *)(iVar4 + 0xa7be3c) = (char)(uVar3 + 1);
  *(undefined4 *)(iVar4 + 0xa7be38) = uVar2;
  return;
}

