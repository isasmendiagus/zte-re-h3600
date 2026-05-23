// module: mt7915.ko
// function: MacTableAssocStaNumGet @ 0x15174
// size: 96 bytes
//

int MacTableAssocStaNumGet(int param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  uVar3 = 0;
  piVar2 = (int *)(param_1 + 0xa1d20);
  iVar4 = 0;
  while( true ) {
    uVar1 = HcGetMaxStaNum(param_1);
    bVar5 = uVar1 <= uVar3;
    uVar3 = uVar3 + 1;
    if (bVar5) break;
    if ((*piVar2 == 0x20001) && (piVar2[0x3f] == 2)) {
      iVar4 = iVar4 + 1;
    }
    piVar2 = piVar2 + 0x530;
  }
  return iVar4;
}

