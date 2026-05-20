// module: mt7915.ko
// function: tr_ctl_exit @ 0xce0b0
// size: 248 bytes
//

undefined4 tr_ctl_exit(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar3 = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  ba_reordering_resource_release(param_1);
  ba_ctl_exit(param_1 + 0x1c0);
  if (iVar3 != 0) {
    iVar5 = 0;
    do {
      iVar1 = iVar5 * 4;
      iVar2 = iVar5 * 8;
      _raw_spin_lock_bh(*(int *)(param_1 + 0x9daa8) + iVar1);
      piVar4 = *(int **)(*(int *)(param_1 + 0x9daac) + iVar5 * 8);
      if (piVar4 != (int *)0x0 && piVar4 != (int *)(*(int *)(param_1 + 0x9daac) + iVar2)) {
        do {
          if (*piVar4 != 0) {
            *(int *)(*piVar4 + 4) = piVar4[1];
          }
          if ((int *)piVar4[1] != (int *)0x0) {
            *(int *)piVar4[1] = *piVar4;
          }
          *piVar4 = 0;
          piVar4[1] = 0;
          netif_tx_wake_queue(*(undefined4 *)(piVar4[2] + 0x240));
          os_free_mem(piVar4);
          piVar4 = *(int **)(*(int *)(param_1 + 0x9daac) + iVar2);
        } while (piVar4 != (int *)0x0 && piVar4 != (int *)(*(int *)(param_1 + 0x9daac) + iVar2));
      }
      iVar5 = iVar5 + 1;
      _raw_spin_unlock_bh(*(int *)(param_1 + 0x9daa8) + iVar1);
    } while (iVar5 != iVar3);
  }
  os_free_mem(*(undefined4 *)(param_1 + 0x9daa4));
  os_free_mem(*(undefined4 *)(param_1 + 0x9daa8));
  os_free_mem(*(undefined4 *)(param_1 + 0x9daac));
  return 0;
}

