// module: mt7915.ko
// function: tr_ctl_init @ 0xcde14
// size: 664 bytes
//

undefined4 tr_ctl_init(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int local_30;
  int local_2c;
  int local_28;
  undefined1 auStack_24 [8];
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  iVar2 = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  ba_ctl_init(param_1,param_1 + 0x1c0);
  iVar3 = ba_reordering_resource_init(param_1,0x2000);
  if (iVar3 != 1) goto LAB_000cde6c;
  uVar4 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar4 & 0x1000) == 0) {
    *(undefined1 *)(param_1 + 0x9daa0) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x9daa0) = 1;
  }
  uVar4 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar4 & 0x100) == 0) {
    *(undefined1 *)(param_1 + 0x9daa3) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x9daa3) = 1;
  }
  os_alloc_mem(param_1,&local_30,iVar2);
  if (local_30 == 0) {
    if (-1 < DebugLevel) {
      printk("%s os_alloc_mem fail\n","tr_ctl_init");
    }
    goto LAB_000cde6c;
  }
  if (iVar2 == 0) {
    *(int *)(param_1 + 0x9daa4) = local_30;
    os_alloc_mem(param_1,&local_2c,0);
    if (local_2c != 0) {
      *(int *)(param_1 + 0x9daa8) = local_2c;
      os_alloc_mem(param_1,&local_28,0);
      if (local_28 != 0) {
        *(int *)(param_1 + 0x9daac) = local_28;
        *(undefined1 *)(param_1 + 0x9dab1) = 0;
LAB_000cdf1c:
        *(undefined1 *)(param_1 + 0x9dab0) = 0;
        __memzero(param_1 + 0x9db64,0x3d94);
        return 0;
      }
      goto LAB_000ce064;
    }
LAB_000ce044:
    if (-1 < DebugLevel) {
      printk("%s os_alloc_mem fail\n","tr_ctl_init");
    }
  }
  else {
    __memzero(local_30,iVar2);
    iVar3 = (int)(short)iVar2 << 2;
    *(int *)(param_1 + 0x9daa4) = local_30;
    os_alloc_mem(param_1,&local_2c,iVar3);
    if (local_2c == 0) goto LAB_000ce044;
    iVar1 = (int)(short)iVar2 << 3;
    __memzero(local_2c,iVar3);
    *(int *)(param_1 + 0x9daa8) = local_2c;
    os_alloc_mem(param_1,&local_28,iVar1);
    if (local_28 != 0) {
      __memzero(local_28,iVar1);
      iVar3 = 0;
      *(undefined1 *)(param_1 + 0x9dab1) = 0;
      *(int *)(param_1 + 0x9daac) = local_28;
      do {
        iVar1 = iVar3 * 4;
        *(undefined1 *)(*(int *)(param_1 + 0x9daa4) + iVar3) = 0;
        *(undefined4 *)(*(int *)(param_1 + 0x9daa8) + iVar3 * 4) = 0;
        OS_SPIN_LOCK_IRQSAVE(*(int *)(param_1 + 0x9daa8) + iVar1,auStack_24);
        iVar5 = *(int *)(param_1 + 0x9daac) + iVar3 * 8;
        *(int *)(*(int *)(param_1 + 0x9daac) + iVar3 * 8) = iVar5;
        iVar3 = iVar3 + 1;
        *(int *)(iVar5 + 4) = iVar5;
        OS_SPIN_UNLOCK_IRQRESTORE(*(int *)(param_1 + 0x9daa8) + iVar1,auStack_24);
      } while (iVar2 != iVar3);
      goto LAB_000cdf1c;
    }
LAB_000ce064:
    if (-1 < DebugLevel) {
      printk("%s os_alloc_mem fail\n","tr_ctl_init");
    }
    os_free_mem(local_2c);
  }
  os_free_mem(local_30);
LAB_000cde6c:
  ba_reordering_resource_release(param_1);
  return 1;
}

