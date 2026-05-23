// module: mt7915.ko
// function: MakeOutgoingFrame @ 0x12cf1c
// size: 116 bytes
//

int MakeOutgoingFrame(int param_1,int *param_2,size_t param_3)

{
  void *__dest;
  undefined1 *puVar1;
  int iVar2;
  undefined4 local_4;
  
  if (param_3 == 0xffffffff) {
    iVar2 = 0;
  }
  else {
    iVar2 = 0;
    puVar1 = &stack0x00000004;
    do {
      __dest = (void *)(param_1 + iVar2);
      iVar2 = iVar2 + param_3;
      memmove(__dest,*(void **)(puVar1 + -8),param_3);
      param_3 = *(size_t *)(puVar1 + -4);
      puVar1 = puVar1 + 8;
    } while (param_3 != 0xffffffff);
  }
  *param_2 = iVar2;
  return iVar2;
}

