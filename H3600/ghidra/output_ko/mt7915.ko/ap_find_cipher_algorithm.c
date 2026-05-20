// module: mt7915.ko
// function: ap_find_cipher_algorithm @ 0x19d64
// size: 212 bytes
//

void ap_find_cipher_algorithm(undefined4 param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_3 + 0x14);
  if ((*(uint *)(param_3 + 0x18) & 0x100) == 0) {
    if (*(char *)(param_3 + 5) == '\x01') {
      iVar2 = *(int *)(param_2 + 0x254);
      *(int *)(param_3 + 100) = iVar2;
      bVar1 = *(byte *)(param_2 + 600);
      *(byte *)(param_3 + 0x6c) = bVar1;
      if ((*(uint *)(param_2 + 0x254) & 0xe) == 0) {
        param_2 = param_2 + 0x279;
      }
      else {
        param_2 = param_2 + (uint)bVar1 * 0x51 + 0x30;
      }
      *(int *)(param_3 + 0x68) = param_2;
    }
    else if (iVar3 == 0) {
      iVar2 = *(int *)(param_3 + 100);
    }
    else {
      iVar2 = *(int *)(iVar3 + 0x2c4);
      *(int *)(param_3 + 100) = iVar2;
      bVar1 = *(byte *)(iVar3 + 0x2c8);
      *(byte *)(param_3 + 0x6c) = bVar1;
      if ((*(uint *)(iVar3 + 0x2c4) & 0xe) == 0) {
        if ((*(uint *)(iVar3 + 0x17c) & 0x30000) == 0) {
          iVar3 = iVar3 + 0x368;
        }
        else {
          iVar3 = iVar3 + 0x380;
        }
        *(int *)(param_3 + 0x68) = iVar3 + 2;
      }
      else {
        *(uint *)(param_3 + 0x68) = iVar3 + (uint)bVar1 * 0x51 + 0x180;
      }
    }
    if (iVar2 == 0) {
      *(undefined4 *)(param_3 + 100) = 1;
    }
    return;
  }
  *(undefined4 *)(param_3 + 0x68) = 0;
  *(uint *)(param_3 + 100) = *(uint *)(param_3 + 100) | 1;
  return;
}

