// module: mt7915.ko
// function: HQA_TxBfProfileTagRead @ 0x272fcc
// size: 480 bytes
//

undefined4 HQA_TxBfProfileTagRead(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  undefined4 uVar4;
  uint uVar5;
  void *__src;
  uint uVar6;
  char *local_24;
  
  *(undefined4 *)(param_1 + 0xa3ae0c) = 0;
  os_alloc_mem(param_1,&local_24,0x200);
  if (local_24 == (char *)0x0) {
    uVar4 = 3;
  }
  else {
    *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) | 0x400;
    uVar1 = *(uint *)(param_3 + 0xc);
    uVar2 = *(uint *)(param_3 + 0x10);
    uVar5 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    uVar1 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
            uVar2 >> 0x18;
    __memzero(local_24,0x200);
    sprintf(local_24,"%02x:%02x",uVar5,uVar1);
    if (0 < DebugLevel) {
      printk("%s: val:%x %x, str:%s\n","HQA_TxBfProfileTagRead",uVar5,uVar1,local_24);
    }
    Set_TxBfProfileTagRead(param_1,local_24);
    wait_for_completion_timeout(param_1 + 0xa3ba38,*(undefined4 *)(param_1 + 0xa3ba48));
    __src = *(void **)(param_1 + 0xa3ae0c);
    if (__src != (void *)0x0) {
      if (*(uint *)(param_1 + 0xa3ae10) >> 2 != 0) {
        puVar3 = (uint *)((int)__src + -4);
        uVar2 = 0;
        do {
          puVar3 = puVar3 + 1;
          uVar6 = *puVar3;
          uVar2 = uVar2 + 1;
          *puVar3 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                    uVar6 >> 0x18;
        } while (uVar2 < *(uint *)(param_1 + 0xa3ae10) >> 2);
        __src = *(void **)(param_1 + 0xa3ae0c);
      }
      if (0 < DebugLevel) {
        printk("%s: val:%x %x, str:%s\n","HQA_TxBfProfileTagRead",uVar5,uVar1,local_24);
      }
      memmove((void *)(param_3 + 0xe),__src,*(size_t *)(param_1 + 0xa3ae10));
      *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) & 0xfffffbff;
      os_free_mem(*(undefined4 *)(param_1 + 0xa3ae0c));
      *(undefined4 *)(param_1 + 0xa3ae0c) = 0;
    }
    if (local_24 == (char *)0x0) {
      uVar4 = 0;
    }
    else {
      uVar4 = 0;
      os_free_mem();
    }
  }
  FUN_0026cdd0(param_3,param_2,*(int *)(param_1 + 0xa3ae10) + 2,uVar4);
  return uVar4;
}

