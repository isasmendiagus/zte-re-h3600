// module: mt7915.ko
// function: tx_flow_block @ 0xce1a8
// size: 808 bytes
//

undefined4 tx_flow_block(int param_1,int param_2,byte param_3,int param_4,byte param_5)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int *local_2c [2];
  
  uVar3 = (uint)param_5;
  uVar1 = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_4 == 1) {
    iVar5 = (int)(short)(ushort)param_5;
    local_2c[0] = (int *)0x0;
    iVar6 = iVar5 * 4;
    _raw_spin_lock_bh(*(int *)(param_1 + 0x9daa8) + iVar6);
    *(byte *)(*(int *)(param_1 + 0x9daa4) + uVar3) =
         param_3 | *(byte *)(*(int *)(param_1 + 0x9daa4) + uVar3);
    piVar4 = (int *)(*(int *)(param_1 + 0x9daac) + iVar5 * 8);
    local_2c[0] = *(int **)(*(int *)(param_1 + 0x9daac) + iVar5 * 8);
    if (piVar4 == local_2c[0]) {
LAB_000ce410:
      os_alloc_mem(0,local_2c,0xc);
      if (local_2c[0] == (int *)0x0) {
        if (-1 < DebugLevel) {
          printk("can not allocate TX_BLOCK_DEV\n");
        }
        _raw_spin_unlock_bh(*(int *)(param_1 + 0x9daa8) + iVar6);
        return 0xffffffff;
      }
      local_2c[0][2] = param_2;
      piVar4 = *(int **)(*(int *)(param_1 + 0x9daac) + iVar5 * 8 + 4);
      *local_2c[0] = *piVar4;
      local_2c[0][1] = (int)piVar4;
      *(int **)(*piVar4 + 4) = local_2c[0];
      *piVar4 = (int)local_2c[0];
      _raw_spin_unlock_bh(*(int *)(param_1 + 0x9daa8) + iVar6);
      if (*(int *)(param_2 + 0x240) != 0) {
        _set_bit(0,*(int *)(param_2 + 0x240) + 0x50);
        return 0;
      }
      warn_slowpath_null("include/linux/netdevice.h",0xa06);
      printk(&_LC156);
      return 0;
    }
    iVar2 = local_2c[0][2];
    while (iVar2 != param_2) {
      local_2c[0] = (int *)*local_2c[0];
      if (piVar4 == local_2c[0]) goto LAB_000ce410;
      iVar2 = local_2c[0][2];
    }
  }
  else {
    if (uVar3 == uVar1) {
      if (uVar3 == 0) {
        return 0;
      }
      iVar6 = 0;
      do {
        iVar5 = iVar6 * 4;
        _raw_spin_lock_bh(*(int *)(param_1 + 0x9daa8) + iVar5);
        *(byte *)(*(int *)(param_1 + 0x9daa4) + iVar6) =
             *(byte *)(*(int *)(param_1 + 0x9daa4) + iVar6) & ~param_3;
        if (*(char *)(*(int *)(param_1 + 0x9daa4) + iVar6) == '\0') {
          iVar2 = iVar6 * 8;
          piVar4 = *(int **)(*(int *)(param_1 + 0x9daac) + iVar6 * 8);
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
            } while (piVar4 != (int *)0x0 && piVar4 != (int *)(*(int *)(param_1 + 0x9daac) + iVar2))
            ;
          }
        }
        iVar6 = iVar6 + 1;
        _raw_spin_unlock_bh(*(int *)(param_1 + 0x9daa8) + iVar5);
      } while (iVar6 != (uVar3 - 1 & 0xff) + 1);
      return 0;
    }
    iVar5 = (int)(short)(ushort)param_5;
    iVar6 = iVar5 * 4;
    _raw_spin_lock_bh(*(int *)(param_1 + 0x9daa8) + iVar6);
    *(byte *)(*(int *)(param_1 + 0x9daa4) + uVar3) =
         *(byte *)(*(int *)(param_1 + 0x9daa4) + uVar3) & ~param_3;
    if (*(char *)(*(int *)(param_1 + 0x9daa4) + uVar3) == '\0') {
      iVar2 = iVar5 * 8;
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
    }
  }
  _raw_spin_unlock_bh(*(int *)(param_1 + 0x9daa8) + iVar6);
  return 0;
}

