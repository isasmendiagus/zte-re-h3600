// module: mt7915.ko
// function: update_rxblk_addr @ 0xc5654
// size: 172 bytes
//

void update_rxblk_addr(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x1c);
  if ((*(uint *)(param_1 + 0x44) & 0x40000) == 0) {
    *(int *)(param_1 + 0x28) = iVar2 + 4;
    *(int *)(param_1 + 0x2c) = iVar2 + 10;
    *(int *)(param_1 + 0x30) = iVar2 + 0x10;
    if ((*(byte *)(iVar2 + 1) & 3) == 3) {
      *(int *)(param_1 + 0x34) = iVar2 + 0x18;
    }
    return;
  }
  bVar1 = *(byte *)(iVar2 + 1) & 3;
  if ((*(byte *)(iVar2 + 1) & 3) == 0) {
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x3c) + 6;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x3c);
    return;
  }
  if (bVar1 == 2) {
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x3c) + 6;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x3c);
    return;
  }
  if (bVar1 == 1) {
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x3c) + 6;
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x3c);
  }
  else {
    *(int *)(param_1 + 0x2c) = iVar2 + 2;
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x3c) + 6;
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x3c);
  }
  return;
}

