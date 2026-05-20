// module: mt7915.ko
// function: sta_find_cipher_algorithm @ 0x5563c
// size: 188 bytes
//

void sta_find_cipher_algorithm(undefined4 param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_3 + 0x14);
  if ((*(uint *)(param_3 + 0x18) & 0x100) != 0) {
    *(undefined4 *)(param_3 + 0x68) = 0;
    *(uint *)(param_3 + 100) = *(uint *)(param_3 + 100) | 1;
    return;
  }
  if (*(char *)(param_3 + 5) == '\x01') {
    *(undefined4 *)(param_3 + 100) = *(undefined4 *)(param_2 + 0x254);
    bVar1 = *(byte *)(param_2 + 600);
    *(byte *)(param_3 + 0x6c) = bVar1;
    if ((*(uint *)(param_2 + 0x254) & 0xe) == 0) {
      param_2 = param_2 + 0x279;
    }
    else {
      param_2 = param_2 + (uint)bVar1 * 0x51 + 0x30;
    }
    *(int *)(param_3 + 0x68) = param_2;
    return;
  }
  *(undefined4 *)(param_3 + 100) = *(undefined4 *)(iVar2 + 0x2c4);
  bVar1 = *(byte *)(iVar2 + 0x2c8);
  *(byte *)(param_3 + 0x6c) = bVar1;
  if ((*(uint *)(iVar2 + 0x2c4) & 0xe) != 0) {
    *(uint *)(param_3 + 0x68) = iVar2 + (uint)bVar1 * 0x51 + 0x180;
    return;
  }
  if ((*(uint *)(iVar2 + 0x17c) & 0x30000) == 0) {
    iVar2 = iVar2 + 0x368;
  }
  else {
    iVar2 = iVar2 + 0x380;
  }
  *(int *)(param_3 + 0x68) = iVar2 + 2;
  return;
}

