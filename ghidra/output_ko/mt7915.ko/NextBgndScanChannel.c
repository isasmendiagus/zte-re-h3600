// module: mt7915.ko
// function: NextBgndScanChannel @ 0x22d07c
// size: 248 bytes
//

void NextBgndScanChannel(int param_1,uint param_2)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  bool bVar7;
  
  iVar4 = 0;
  *(undefined1 *)(param_1 + 0xa7905c) = 0;
  iVar5 = *(byte *)(param_1 + 0xa78ad1) - 1;
  if (iVar5 < 1) {
    return;
  }
  do {
    if ((*(byte *)(param_1 + iVar4 * 0x18 + 0xa78ad5) == param_2) && (iVar4 < iVar5)) {
      iVar3 = iVar4 + 1;
      if (*(char *)(param_1 + iVar3 * 0x18 + 0xa78ad9) != '\x01') {
LAB_0022d138:
        iVar4 = param_1 + iVar3 * 0x18;
        *(undefined1 *)(param_1 + 0xa7905c) = *(undefined1 *)(iVar4 + 0xa78ad5);
        uVar2 = *(undefined1 *)(iVar4 + 0xa78ad6);
        *(char *)(param_1 + 0xa7922f) = (char)iVar3;
        *(undefined1 *)(param_1 + 0xa7905d) = uVar2;
        return;
      }
      pcVar6 = (char *)(param_1 + iVar4 * 0x18 + 0xa78b09);
      while (bVar7 = iVar3 != iVar5, iVar3 = iVar3 + 1, iVar4 = iVar5, bVar7) {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 0x18;
        if (cVar1 != '\x01') goto LAB_0022d138;
      }
    }
    iVar4 = iVar4 + 1;
    if (iVar5 <= iVar4) {
      return;
    }
  } while( true );
}

