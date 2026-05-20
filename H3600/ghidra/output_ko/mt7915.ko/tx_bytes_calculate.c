// module: mt7915.ko
// function: tx_bytes_calculate @ 0xcdc64
// size: 208 bytes
//

void tx_bytes_calculate(undefined4 param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  
  bVar1 = *(byte *)(param_2 + 0x2e);
  if (bVar1 < 2) {
    sVar3 = (ushort)*(byte *)(param_2 + 0x35) + (ushort)*(byte *)(param_2 + 0x34) + 0x20 +
            (short)*(undefined4 *)(param_2 + 0x28);
    *(short *)(param_2 + 0x36) = sVar3;
    if (bVar1 == 0) {
      return;
    }
  }
  else {
    sVar3 = (ushort)*(byte *)(param_2 + 0x34) +
            (ushort)*(byte *)(param_2 + 0x35) + *(short *)(param_2 + 0x36) +
            (short)*(undefined4 *)(param_2 + 0x28);
    *(short *)(param_2 + 0x36) = sVar3;
  }
  iVar4 = *(int *)(param_2 + 0xc);
  if (0x5dc < ((int)*(char *)(iVar4 + 0x34) & 0xffffU |
              ((int)*(char *)(iVar4 + 0x35) & 0xffffU) << 8)) {
    *(short *)(param_2 + 0x36) = sVar3 + 8;
  }
  if ((*(byte *)(iVar4 + 0x30) & 0x10) != 0) {
    if (*(char *)(*(int *)(param_2 + 0x10) + 0x8f8) == '\0') {
      sVar3 = *(short *)(param_2 + 0x36) + -4;
    }
    else {
      sVar3 = *(short *)(param_2 + 0x36) + 6;
    }
    *(short *)(param_2 + 0x36) = sVar3;
  }
  if (bVar1 == 3) {
    return;
  }
  uVar2 = *(ushort *)(param_2 + 0x36);
  if ((uVar2 & 3) != 0) {
    *(ushort *)(param_2 + 0x36) = (uVar2 + 4) - (uVar2 & 3);
  }
  return;
}

