// module: mt7915.ko
// function: RT_SHA1_Append @ 0x125994
// size: 152 bytes
//

void RT_SHA1_Append(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  size_t __n;
  
  if (param_3 != 0) {
    uVar2 = 0;
    do {
      iVar1 = *(int *)(param_1 + 0x60);
      __n = param_3 - uVar2;
      if (__n + iVar1 < 0x40) {
        memmove((void *)(param_1 + iVar1 + 0x20),(void *)(param_2 + uVar2),__n);
        *(size_t *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + __n;
        break;
      }
      memmove((void *)(param_1 + iVar1 + 0x20),(void *)(param_2 + uVar2),0x40 - iVar1);
      iVar1 = *(int *)(param_1 + 0x60);
      *(undefined4 *)(param_1 + 0x60) = 0x40;
      uVar2 = uVar2 + (0x40 - iVar1);
      RT_SHA1_Hash(param_1);
    } while (param_3 != uVar2);
  }
  uVar2 = *(uint *)(param_1 + 0x18);
  *(uint *)(param_1 + 0x18) = uVar2 + param_3;
  *(uint *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + (uint)CARRY4(uVar2,param_3);
  return;
}

