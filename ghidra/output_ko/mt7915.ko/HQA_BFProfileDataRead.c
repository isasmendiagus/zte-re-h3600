// module: mt7915.ko
// function: HQA_BFProfileDataRead @ 0x272ab0
// size: 684 bytes
//

undefined4 HQA_BFProfileDataRead(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  void *__src;
  uint *puVar5;
  uint uVar6;
  size_t __n;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  char *local_2c [2];
  
  iVar1 = DebugLevel;
  *(undefined4 *)(param_1 + 0xa3ae0c) = 0;
  os_alloc_mem(param_1,local_2c,0x200);
  if (local_2c[0] == (char *)0x0) {
    iVar10 = 2;
    uVar8 = 3;
  }
  else {
    DebugLevel = 1;
    *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) | 0x400;
    uVar2 = *(uint *)(param_3 + 0xc);
    uVar3 = *(uint *)(param_3 + 0x10);
    uVar6 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
            uVar2 >> 0x18;
    uVar2 = *(uint *)(param_3 + 0x14);
    uVar4 = *(uint *)(param_3 + 0x18);
    uVar3 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
            uVar3 >> 0x18;
    uVar9 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
            uVar2 >> 0x18;
    uVar2 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
            uVar4 >> 0x18;
    uVar4 = (uVar2 + 1) - uVar9;
    *(uint *)(param_3 + 0xe) =
         uVar4 * 0x1000000 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
         uVar4 >> 0x18;
    if (uVar2 < uVar9) {
      iVar10 = 6;
    }
    else {
      iVar10 = 4;
      do {
        *(undefined4 *)(param_1 + 0xa3ae0c) = 0;
        __memzero(local_2c[0],0x200);
        uVar4 = uVar9 >> 8 & 0xff;
        if (2 < DebugLevel) {
          printk("%s: idx:%02x fgBFer:%02x Sub_H:%02x Sub_L:%02x subidx:%d\n",
                 "HQA_BFProfileDataRead",uVar6,uVar3,uVar4,uVar9 & 0xff,uVar9);
        }
        sprintf(local_2c[0],"%02x:%02x:%02x:%02x",uVar6,uVar3,uVar4,uVar9 & 0xff);
        Set_TxBfProfileDataRead(param_1,local_2c[0]);
        wait_for_completion_timeout(param_1 + 0xa3ba38,*(undefined4 *)(param_1 + 0xa3ba48));
        __src = *(void **)(param_1 + 0xa3ae0c);
        if (__src == (void *)0x0) {
          iVar10 = iVar10 + 2;
          goto LAB_00272cc0;
        }
        __n = *(uint *)(param_1 + 0xa3ae10);
        if (__n >> 2 != 0) {
          puVar5 = (uint *)((int)__src + -4);
          uVar4 = 0;
          do {
            puVar5 = puVar5 + 1;
            uVar7 = *puVar5;
            uVar4 = uVar4 + 1;
            *puVar5 = uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 |
                      uVar7 >> 0x18;
            __n = *(uint *)(param_1 + 0xa3ae10);
          } while (uVar4 < __n >> 2);
          __src = *(void **)(param_1 + 0xa3ae0c);
        }
        uVar9 = uVar9 + 1;
        memmove((void *)(param_3 + iVar10 + 0xe),__src,__n);
        iVar10 = iVar10 + *(int *)(param_1 + 0xa3ae10);
        os_free_mem(*(undefined4 *)(param_1 + 0xa3ae0c));
        *(undefined4 *)(param_1 + 0xa3ae0c) = 0;
      } while (uVar9 <= uVar2);
      iVar10 = iVar10 + 2;
    }
    *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) & 0xfffffbff;
LAB_00272cc0:
    if (local_2c[0] == (char *)0x0) {
      uVar8 = 0;
    }
    else {
      uVar8 = 0;
      os_free_mem(local_2c[0]);
    }
  }
  FUN_0026cdd0(param_3,param_2,iVar10,uVar8);
  DebugLevel = iVar1;
  return uVar8;
}

