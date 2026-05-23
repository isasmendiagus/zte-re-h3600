// module: mt7915.ko
// function: tx_flow_set_state_block @ 0xce5a8
// size: 444 bytes
//

undefined4
tx_flow_set_state_block(int param_1,int param_2,undefined4 param_3,int param_4,byte param_5)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  uVar3 = (uint)param_5;
  if (param_4 == 1) {
    _raw_spin_lock_bh(*(int *)(param_1 + 0x9daa8) + uVar3 * 4);
    *(byte *)(*(int *)(param_1 + 0x9daa4) + uVar3) =
         (byte)param_3 | *(byte *)(*(int *)(param_1 + 0x9daa4) + uVar3);
    _raw_spin_unlock_bh(*(int *)(param_1 + 0x9daa8) + uVar3 * 4);
    if (param_2 == 0) {
      piVar4 = (int *)(param_1 + 8);
      do {
        piVar4 = piVar4 + 1;
        if (((int *)*piVar4 != (int *)0x0) && (iVar2 = *(int *)*piVar4, iVar2 != 0)) {
          iVar2 = *(int *)(iVar2 + 0x240);
          if (iVar2 == 0) {
            warn_slowpath_null("include/linux/netdevice.h",0xa06);
            printk(&_LC156);
          }
          else {
            _set_bit(0,iVar2 + 0x50);
          }
        }
      } while (piVar4 != (int *)(param_1 + 0x1a8));
    }
    else if (*(int *)(param_2 + 0x240) == 0) {
      warn_slowpath_null("include/linux/netdevice.h",0xa06);
      printk(&_LC156);
    }
    else {
      _set_bit(0,*(int *)(param_2 + 0x240) + 0x50);
    }
    *(undefined1 *)(param_1 + 0x9dab0) = 1;
    *(int *)(param_1 + 0x9dba0) = *(int *)(param_1 + 0x9dba0) + 1;
    return 0;
  }
  uVar1 = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  _raw_spin_lock_bh(*(int *)(param_1 + 0x9daa8) + uVar3 * 4);
  *(byte *)(*(int *)(param_1 + 0x9daa4) + uVar3) =
       *(byte *)(*(int *)(param_1 + 0x9daa4) + uVar3) & ~(byte)param_3;
  _raw_spin_unlock_bh(*(int *)(param_1 + 0x9daa8) + uVar3 * 4);
  iVar2 = tx_flow_check_state(param_1,param_3,uVar1);
  if (iVar2 == 0) {
    if (param_2 == 0) {
      piVar4 = (int *)(param_1 + 8);
      do {
        piVar4 = piVar4 + 1;
        if (((int *)*piVar4 != (int *)0x0) && (iVar2 = *(int *)*piVar4, iVar2 != 0)) {
          netif_tx_wake_queue(*(undefined4 *)(iVar2 + 0x240));
        }
      } while (piVar4 != (int *)(param_1 + 0x1a8));
    }
    else {
      netif_tx_wake_queue(*(undefined4 *)(param_2 + 0x240));
    }
  }
  *(undefined1 *)(param_1 + 0x9dab0) = 0;
  return 0;
}

