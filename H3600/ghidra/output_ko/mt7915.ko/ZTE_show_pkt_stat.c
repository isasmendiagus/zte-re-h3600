// module: mt7915.ko
// function: ZTE_show_pkt_stat @ 0x15b950
// size: 144 bytes
//

undefined4 ZTE_show_pkt_stat(int *param_1)

{
  byte bVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  bool bVar5;
  
  bVar1 = *(byte *)(*param_1 + 0x3c);
  if (*(char *)((int)param_1 + (uint)bVar1 * 0x5834 + 0x2bca4b) != '\0') {
    uVar4 = 0;
    piVar3 = param_1 + 0x28748;
    while( true ) {
      uVar2 = HcGetMaxStaNum(param_1);
      bVar5 = uVar2 <= uVar4;
      uVar4 = uVar4 + 1;
      if (bVar5) break;
      if (((piVar3 != (int *)0x0) && (*piVar3 != 0)) &&
         ((uint)*(byte *)((int)piVar3 + 0xe5) == (uint)bVar1)) {
        FUN_0015630c(param_1,piVar3);
      }
      piVar3 = piVar3 + 0x530;
    }
    return 1;
  }
  return 0;
}

