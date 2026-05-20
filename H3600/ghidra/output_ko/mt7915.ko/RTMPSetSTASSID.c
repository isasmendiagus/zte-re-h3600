// module: mt7915.ko
// function: RTMPSetSTASSID @ 0xef218
// size: 224 bytes
//

void RTMPSetSTASSID(undefined4 param_1,undefined4 param_2,char *param_3)

{
  int iVar1;
  size_t sVar2;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 == 0) {
    return;
  }
  sVar2 = strlen(param_3);
  *(char *)(iVar1 + 0x212426) = (char)sVar2;
  __memzero((void *)(iVar1 + 0x212406),0x20);
  memmove((void *)(iVar1 + 0x212406),param_3,(uint)*(byte *)(iVar1 + 0x212426));
  *(undefined1 *)(iVar1 + 0x212427) = *(undefined1 *)(iVar1 + 0x212426);
  __memzero((void *)(iVar1 + 0x21242e),0x20);
  memmove((void *)(iVar1 + 0x21242e),param_3,(uint)*(byte *)(iVar1 + 0x212427));
  *(undefined1 *)(iVar1 + 0x4160) = *(undefined1 *)(iVar1 + 0x212426);
  __memzero((void *)(iVar1 + 0x4140),0x20);
  memmove((void *)(iVar1 + 0x4140),param_3,(uint)*(byte *)(iVar1 + 0x4160));
  *(undefined1 *)(iVar1 + 0x4139) = *(undefined1 *)(iVar1 + 0x212426);
  __memzero((void *)(iVar1 + 0x4119),0x20);
  memmove((void *)(iVar1 + 0x4119),param_3,(uint)*(byte *)(iVar1 + 0x4139));
  return;
}

