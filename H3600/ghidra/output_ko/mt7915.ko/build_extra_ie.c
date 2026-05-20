// module: mt7915.ko
// function: build_extra_ie @ 0x146ef8
// size: 84 bytes
//

undefined4 build_extra_ie(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  
  if (*(char *)(param_2 + 1) != '\x04') {
    return 0;
  }
  iVar1 = param_2[4];
  if (*(size_t *)(iVar1 + 0xbc4) != 0) {
    if (*(void **)(iVar1 + 0xbc0) != (void *)0x0) {
      memmove((void *)*param_2,*(void **)(iVar1 + 0xbc0),*(size_t *)(iVar1 + 0xbc4));
      return *(undefined4 *)(iVar1 + 0xbc4);
    }
    return 0;
  }
  return 0;
}

