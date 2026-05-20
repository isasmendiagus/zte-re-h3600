// module: mt7915.ko
// function: ZTE_Bss_NotifyAD @ 0x16098c
// size: 132 bytes
//

undefined4 ZTE_Bss_NotifyAD(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = 0;
  while( true ) {
    uVar1 = HcGetMaxStaNum(param_1);
    uVar5 = uVar4 & 0xffff;
    uVar4 = uVar4 + 1;
    iVar2 = uVar5 * 0x14c0;
    iVar3 = param_1 + iVar2;
    if (uVar1 <= uVar5) break;
    if (((param_1 + iVar2 + 0xa1d20 != 0) && (*(int *)(iVar3 + 0xa1d28) != 0)) &&
       (*(int *)(iVar3 + 0xa1d20) == 0x20001)) {
      ZTE_Notify_Node_AD(1);
    }
  }
  return 1;
}

