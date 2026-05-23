// module: mt7915.ko
// function: wifi_sys_update_bssinfo @ 0x104a50
// size: 468 bytes
//

undefined4 wifi_sys_update_bssinfo(int param_1,int param_2,void *param_3)

{
  int iVar1;
  int *piVar2;
  void *__dest;
  int iVar3;
  int local_20;
  void *local_1c;
  
  __dest = (void *)(param_2 + 0x98c);
  if (*(uint *)((int)param_3 + 4) < 2) {
    _raw_spin_lock_bh(param_1 + 0xa7bf00);
    piVar2 = *(int **)(param_1 + 0xa7bee4);
    do {
      if ((int *)(param_1 + 0xa7bee4) == piVar2) {
LAB_00104bac:
        _raw_spin_unlock_bh(param_1 + 0xa7bf00);
        BssInfoArgumentUnLink(param_1,param_2);
        return 0;
      }
      if (__dest == piVar2 + -0x43) {
        if (*(int *)(param_2 + 0xa98) != 0) {
          *(undefined4 *)(*(int *)(param_2 + 0xa98) + 4) = *(undefined4 *)(param_2 + 0xa9c);
        }
        if (*(undefined4 **)(param_2 + 0xa9c) != (undefined4 *)0x0) {
          **(undefined4 **)(param_2 + 0xa9c) = *(undefined4 *)(param_2 + 0xa98);
        }
        *(undefined4 *)(param_2 + 0xa98) = 0;
        *(undefined4 *)(param_2 + 0xa9c) = 0;
        *(int *)(param_1 + 0xa7bee0) = *(int *)(param_1 + 0xa7bee0) + -1;
        goto LAB_00104bac;
      }
      piVar2 = (int *)*piVar2;
    } while( true );
  }
  iVar3 = param_1 + 0xa7bf00;
  os_move_mem(__dest,param_3,0x10c);
  _raw_spin_lock_bh(iVar3);
  piVar2 = *(int **)(param_1 + 0xa7bee4);
  do {
    if ((int *)(param_1 + 0xa7bee4) == piVar2) {
      piVar2 = *(int **)(param_1 + 0xa7bee8);
      iVar1 = *piVar2;
      *(int **)(param_2 + 0xa9c) = piVar2;
      *(int *)(param_2 + 0xa98) = iVar1;
      *(int *)(*piVar2 + 4) = param_2 + 0xa98;
      *piVar2 = param_2 + 0xa98;
      *(int *)(param_2 + 0xa94) = param_2;
      *(int *)(param_1 + 0xa7bee0) = *(int *)(param_1 + 0xa7bee0) + 1;
      _raw_spin_unlock_bh(iVar3);
LAB_00104aec:
      *(undefined4 *)(param_2 + 0x990) = 3;
      *(undefined4 *)(param_2 + 0x994) = 1;
      local_20 = param_2;
      local_1c = __dest;
      mt_notify_call_chain(*(int *)(param_2 + 8) + 0xa7bef8,4,&local_20);
      return 0;
    }
    if (__dest == piVar2 + -0x43) {
      _raw_spin_unlock_bh(iVar3);
      if (2 < DebugLevel) {
        printk("%s(): BssInfo %d already exist","add_bssinfo",*(undefined1 *)(param_2 + 0x999));
      }
      goto LAB_00104aec;
    }
    piVar2 = (int *)*piVar2;
  } while( true );
}

