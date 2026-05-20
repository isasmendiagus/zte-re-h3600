// module: mt7915.ko
// function: SetEEPROMValChange @ 0x25efcc
// size: 200 bytes
//

void SetEEPROMValChange(int param_1,int param_2,undefined1 param_3)

{
  char *pcVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  
  puVar5 = EEPROMValChange;
  iVar3 = 0;
  puVar6 = puVar5;
  while ((iVar4 = iVar3 * 8, *(int *)(EEPROMValChange + iVar3 * 8) != param_2 || (puVar6[4] == '\0')
         )) {
    iVar3 = iVar3 + 1;
    puVar6 = puVar6 + 8;
    if (iVar3 == 0x40) {
      iVar3 = 0;
      while (pcVar1 = puVar5 + 4, puVar5 = puVar5 + 8, *pcVar1 != '\0') {
        iVar3 = iVar3 + 1;
        if (iVar3 == 0x40) {
          return;
        }
      }
      iVar4 = iVar3 << 3;
LAB_0025f02c:
      *(int *)(EEPROMValChange + iVar3 * 8) = param_2;
      iVar3 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
      EEPROMValChange[iVar4 + 4] = 1;
      EEPROMValChange[iVar4 + 5] = 1;
      uVar2 = *(undefined1 *)(iVar3 + param_2);
      EEPROMValChange[iVar4 + 7] = param_3;
      EEPROMValChange[iVar4 + 6] = uVar2;
      *(undefined1 *)(iVar3 + param_2) = param_3;
      return;
    }
  }
  if (EEPROMValChange[iVar4 + 5] != '\0') {
    return;
  }
  goto LAB_0025f02c;
}

