// module: mt7915.ko
// function: SetEEPROMTxPowerPlus @ 0x25f094
// size: 296 bytes
//

void SetEEPROMTxPowerPlus(int param_1,int param_2,char param_3)

{
  int iVar1;
  char *pcVar2;
  undefined1 uVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  undefined1 *puVar7;
  int iVar8;
  byte bVar9;
  undefined1 *puVar10;
  
  puVar7 = EEPROMValChange;
  iVar6 = 0;
  puVar10 = puVar7;
  while ((*(int *)(EEPROMValChange + iVar6 * 8) != param_2 || (puVar10[4] == '\0'))) {
    iVar6 = iVar6 + 1;
    puVar10 = puVar10 + 8;
    if (iVar6 == 0x40) {
      iVar6 = 0;
      while (pcVar2 = puVar7 + 4, puVar7 = puVar7 + 8, *pcVar2 != '\0') {
        iVar6 = iVar6 + 1;
        if (iVar6 == 0x40) {
          return;
        }
      }
LAB_0025f0f4:
      iVar8 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
      bVar9 = *(byte *)(iVar8 + param_2) & 0xc0;
      bVar4 = *(byte *)(iVar8 + param_2) & 0x3f;
      if (bVar9 == 0x80) {
        bVar4 = -bVar4;
      }
      else if (bVar9 != 0xc0) {
        bVar4 = 0;
      }
      bVar4 = bVar4 + param_3;
      if (bVar4 < 0x11) {
        cVar5 = bVar4 - 0x40;
      }
      else {
        if (0xf < (byte)(bVar4 + 0x10)) {
          return;
        }
        cVar5 = -0x80 - bVar4;
      }
      iVar1 = iVar6 * 8;
      *(int *)(EEPROMValChange + iVar6 * 8) = param_2;
      EEPROMValChange[iVar1 + 4] = 1;
      EEPROMValChange[iVar1 + 5] = 1;
      uVar3 = *(undefined1 *)(iVar8 + param_2);
      EEPROMValChange[iVar1 + 7] = cVar5;
      EEPROMValChange[iVar1 + 6] = uVar3;
      *(char *)(iVar8 + param_2) = cVar5;
      return;
    }
  }
  if (EEPROMValChange[iVar6 * 8 + 5] != '\0') {
    return;
  }
  goto LAB_0025f0f4;
}

