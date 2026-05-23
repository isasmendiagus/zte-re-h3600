// module: mt7915.ko
// function: BigInteger_Free_AllocSize @ 0x1fb074
// size: 92 bytes
//

void BigInteger_Free_AllocSize(int *param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  if (iVar2 == 0) {
    return;
  }
  if (*(int *)(iVar2 + 0xc) == 0) {
    return;
  }
  uVar1 = *(undefined1 *)(iVar2 + 0x20);
  os_free_mem(*(int *)(iVar2 + 0xc));
  __memzero(*param_1,0x24);
  *(undefined4 *)(*param_1 + 0xc) = 0;
  *(undefined4 *)(*param_1 + 0x1c) = 1;
  *(undefined1 *)(*param_1 + 0x20) = uVar1;
  return;
}

