// module: mt7915.ko
// function: NetworkTypeInUseSanity @ 0x11237c
// size: 328 bytes
//

int NetworkTypeInUseSanity(int param_1)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  uint uVar4;
  
  if (*(byte *)(param_1 + 0xc) < 0xf) {
    if (*(char *)(param_1 + 0x26) != '\0') {
      pbVar2 = (byte *)(param_1 + 0x19);
      do {
        pbVar2 = pbVar2 + 1;
        bVar3 = *pbVar2 & 0x7f;
        if (((bVar3 - 2 & 0xfd) != 0) && (bVar3 != 0x16 && bVar3 != 0xb)) goto LAB_001123c8;
      } while (pbVar2 != (byte *)(param_1 + (byte)(*(char *)(param_1 + 0x26) - 1) + 0x1a));
    }
    if (*(char *)(param_1 + 0x33) == '\0') {
      uVar4 = *(uint *)(param_1 + 0xac8);
      if ((uVar4 & 1) == 0) {
        iVar1 = 1;
        goto LAB_001123d8;
      }
    }
    else {
      pbVar2 = (byte *)(param_1 + 0x19);
      do {
        pbVar2 = pbVar2 + 1;
        bVar3 = *pbVar2 & 0x7f;
        if (((bVar3 - 2 & 0xfd) != 0) && (bVar3 != 0x16 && bVar3 != 0xb)) goto LAB_001123c8;
      } while (pbVar2 != (byte *)(param_1 + (byte)(*(char *)(param_1 + 0x33) - 1) + 0x1a));
      uVar4 = *(uint *)(param_1 + 0xac8);
      if ((uVar4 & 1) == 0) {
        if ((uVar4 & 0x10) == 0) {
          iVar1 = 1;
        }
        else {
          iVar1 = 8;
        }
        return iVar1;
      }
    }
    goto LAB_00112420;
  }
  uVar4 = *(uint *)(param_1 + 0xac8);
  if ((uVar4 & 1) == 0) {
    iVar1 = 2;
LAB_001123f4:
    if ((uVar4 & 0x10) == 0) {
      return iVar1;
    }
    if (iVar1 == 2 || iVar1 == 7) {
      return 9;
    }
    goto LAB_0011242c;
  }
  if ((uVar4 & 4) != 0) {
    iVar1 = 7;
    goto LAB_001123f4;
  }
  iVar1 = 5;
  goto LAB_00112424;
LAB_001123c8:
  uVar4 = *(uint *)(param_1 + 0xac8);
  if ((uVar4 & 1) == 0) {
    iVar1 = 3;
LAB_001123d8:
    if ((uVar4 & 0x10) != 0) {
      iVar1 = 8;
    }
    return iVar1;
  }
LAB_00112420:
  iVar1 = 6;
LAB_00112424:
  if ((uVar4 & 0x10) == 0) {
    return iVar1;
  }
LAB_0011242c:
  if (iVar1 == 5) {
    iVar1 = 9;
  }
  else {
    iVar1 = 8;
  }
  return iVar1;
}

