// module: mt7915.ko
// function: BN_STACK_push @ 0x20ecc4
// size: 172 bytes
//

void BN_STACK_push(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  void *local_14;
  
  iVar1 = param_1[1];
  if (iVar1 == param_1[2]) {
    if (iVar1 == 0) {
      iVar1 = 0x80;
      uVar2 = 0x20;
    }
    else {
      uVar2 = (uint)(iVar1 * 3) >> 1;
      iVar1 = uVar2 << 2;
    }
    os_alloc_mem(0,&local_14,iVar1);
    if (local_14 == (void *)0x0) {
      return;
    }
    if (param_1[1] != 0) {
      memcpy(local_14,(void *)*param_1,param_1[1] << 2);
    }
    if (*param_1 != 0) {
      os_free_mem();
    }
    iVar1 = param_1[1];
    param_1[2] = uVar2;
    *param_1 = (int)local_14;
  }
  else {
    local_14 = (void *)*param_1;
  }
  param_1[1] = iVar1 + 1;
  *(undefined4 *)((int)local_14 + iVar1 * 4) = param_2;
  return;
}

