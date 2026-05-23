// module: mt7915.ko
// function: MT_ATESampleRssi @ 0x27e5a8
// size: 292 bytes
//

undefined4 MT_ATESampleRssi(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;
  char *pcVar6;
  ushort *puVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  
  bVar1 = "SetPartProfileParameters"[param_1 + 0x18];
  if (bVar1 >> 4 != 0) {
    puVar4 = (undefined1 *)(param_1 + 0xa3b767);
    puVar7 = (ushort *)(param_1 + 0xa3b77c);
    pcVar6 = (char *)(param_1 + 0xa3b770);
    pcVar9 = (char *)(param_1 + 0xa3b778);
    pcVar10 = (char *)(param_1 + 0xa3b76c);
    pcVar8 = (char *)(param_1 + 0xa3b774);
    uVar5 = 0xffffffff;
    do {
      uVar5 = uVar5 + 1;
      if (*(char *)(param_2 + 0x58) != '\0') {
        iVar3 = ConvertToRssi(param_1,param_2 + 0x58,uVar5 & 0xff);
        cVar2 = (char)iVar3;
        *pcVar10 = cVar2;
        if (*pcVar8 < iVar3) {
          *pcVar8 = cVar2;
        }
        if (iVar3 < *pcVar9) {
          *pcVar9 = cVar2;
        }
        iVar3 = ((uint)*puVar7 - (int)*pcVar6) + iVar3;
        *puVar7 = (ushort)iVar3;
        *pcVar6 = (char)(iVar3 * 0x10000 >> 0x13);
      }
      puVar7 = puVar7 + 1;
      pcVar6 = pcVar6 + 1;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
      pcVar8 = pcVar8 + 1;
      puVar4 = puVar4 + 1;
      *puVar4 = *(undefined1 *)(param_2 + 0x5c);
      param_2 = param_2 + 1;
    } while (uVar5 != (bVar1 >> 4) - 1);
  }
  *(int *)(param_1 + 0xa3b754) = *(int *)(param_1 + 0xa3b754) + 1;
  return 0;
}

