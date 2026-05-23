// module: mt7915.ko
// function: wifi_sys_update_devinfo @ 0x1048b4
// size: 408 bytes
//

undefined4 wifi_sys_update_devinfo(int param_1,int param_2,void *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int local_20 [2];
  
  os_move_mem((void *)(param_2 + 0xaa0),param_3,0x14);
  if (*(char *)((int)param_3 + 8) == '\0') {
    _raw_spin_lock_bh(param_1 + 0xa7bf00);
    if (*(int *)(param_2 + 0xab4) != 0) {
      *(undefined4 *)(*(int *)(param_2 + 0xab4) + 4) = *(undefined4 *)(param_2 + 0xab8);
    }
    if (*(undefined4 **)(param_2 + 0xab8) != (undefined4 *)0x0) {
      **(undefined4 **)(param_2 + 0xab8) = *(undefined4 *)(param_2 + 0xab4);
    }
    *(undefined4 *)(param_2 + 0xab4) = 0;
    *(undefined4 *)(param_2 + 0xab8) = 0;
    *(int *)(param_1 + 0xa7bed4) = *(int *)(param_1 + 0xa7bed4) + -1;
    _raw_spin_unlock_bh(param_1 + 0xa7bf00);
    HcReleaseRadioForWdev(*(undefined4 *)(param_2 + 8),param_2);
    *(undefined1 *)(param_2 + 0x29) = 0xff;
    return 0;
  }
  iVar3 = param_1 + 0xa7bf00;
  _raw_spin_lock_bh(iVar3);
  piVar2 = *(int **)(param_1 + 0xa7bed8);
  do {
    if ((int *)(param_1 + 0xa7bed8) == piVar2) {
      piVar2 = *(int **)(param_1 + 0xa7bedc);
      iVar1 = *piVar2;
      *(int **)(param_2 + 0xab8) = piVar2;
      *(int *)(param_2 + 0xab4) = iVar1;
      *(int *)(*piVar2 + 4) = param_2 + 0xab4;
      *piVar2 = param_2 + 0xab4;
      *(int *)(param_2 + 0xab0) = param_2;
      *(int *)(param_1 + 0xa7bed4) = *(int *)(param_1 + 0xa7bed4) + 1;
      _raw_spin_unlock_bh(iVar3);
LAB_001049c0:
      local_20[1] = 0;
      local_20[0] = param_2;
      mt_notify_call_chain(*(int *)(param_2 + 8) + 0xa7bef8,0,local_20);
      return 0;
    }
    if ((void *)(param_2 + 0xaa0) == piVar2 + -5) {
      _raw_spin_unlock_bh(iVar3);
      if (2 < DebugLevel) {
        printk("%s(): DevInfo %d already exist","add_devinfo",*(undefined1 *)(param_2 + 0xaa0));
      }
      goto LAB_001049c0;
    }
    piVar2 = (int *)*piVar2;
  } while( true );
}

