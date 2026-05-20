// module: mt7915.ko
// function: HQA_BFQdRead @ 0x272380
// size: 396 bytes
//

undefined4 HQA_BFQdRead(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  void *__src;
  char *local_28;
  uint local_24;
  
  *(undefined4 *)(param_1 + 0xa3ae0c) = 0;
  local_24 = 0;
  os_alloc_mem(param_1,&local_28,0x200);
  if (local_28 == (char *)0x0) {
    uVar2 = 3;
  }
  else {
    *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) | 0x400;
    uVar1 = *(uint *)(param_3 + 0xc);
    uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    local_24 = uVar1;
    __memzero(local_28,0x200);
    sprintf(local_28,"%d",uVar1);
    if (0 < DebugLevel) {
      printk("%s, val:%u, str:%s\n","HQA_BFQdRead",uVar1,local_28);
    }
    Set_TxBfQdRead(param_1,local_28);
    wait_for_completion_timeout(param_1 + 0xa3ba38,*(undefined4 *)(param_1 + 0xa3ba48));
    __src = *(void **)(param_1 + 0xa3ae0c);
    if (__src != (void *)0x0) {
      iVar3 = 0;
      do {
        if (2 < DebugLevel) {
          printk("DWORD%d:%08x\n",iVar3,*(undefined4 *)((int)__src + iVar3 * 4));
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 != 0xe);
      memmove((void *)(param_3 + 0xe),__src,*(size_t *)(param_1 + 0xa3ae10));
      *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) & 0xfffffbff;
      os_free_mem(*(undefined4 *)(param_1 + 0xa3ae0c));
      *(undefined4 *)(param_1 + 0xa3ae0c) = 0;
    }
    if (local_28 == (char *)0x0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0;
      os_free_mem();
    }
  }
  FUN_0026cdd0(param_3,param_2,*(int *)(param_1 + 0xa3ae10) + 2,uVar2);
  return uVar2;
}

