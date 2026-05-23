// module: mt7915.ko
// function: RT_SHA256_Append @ 0x125da0
// size: 152 bytes
//

void RT_SHA256_Append(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  size_t __n;
  
  if (param_3 != 0) {
    uVar2 = 0;
    do {
      iVar1 = *(int *)(param_1 + 0x68);
      __n = param_3 - uVar2;
      if (__n + iVar1 < 0x40) {
        memmove((void *)(param_1 + iVar1 + 0x28),(void *)(param_2 + uVar2),__n);
        *(size_t *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + __n;
        break;
      }
      memmove((void *)(param_1 + iVar1 + 0x28),(void *)(param_2 + uVar2),0x40 - iVar1);
      iVar1 = *(int *)(param_1 + 0x68);
      *(undefined4 *)(param_1 + 0x68) = 0x40;
      uVar2 = uVar2 + (0x40 - iVar1);
      RT_SHA256_Hash(param_1);
    } while (param_3 != uVar2);
  }
  uVar2 = *(uint *)(param_1 + 0x20);
  *(uint *)(param_1 + 0x20) = uVar2 + param_3;
  *(uint *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + (uint)CARRY4(uVar2,param_3);
  return;
}

