// module: mt7915.ko
// function: wifi_sys_update_starec @ 0x104c28
// size: 436 bytes
//

undefined4 wifi_sys_update_starec(int param_1,void *param_2)

{
  int iVar1;
  int *piVar2;
  void *__dest;
  int iVar3;
  int iVar4;
  int local_20;
  int local_1c;
  
  iVar3 = *(int *)((int)param_2 + 0xcc);
  __dest = (void *)(iVar3 + 0x3e0);
  os_move_mem(__dest,param_2,0xd0);
  iVar4 = param_1 + 0xa7bf00;
  if (*(char *)((int)param_2 + 8) == '\0') {
    _raw_spin_lock_bh(iVar4);
    piVar2 = *(int **)(param_1 + 0xa7bef0);
    do {
      if ((int *)(param_1 + 0xa7bef0) == piVar2) {
LAB_00104d70:
        _raw_spin_unlock_bh(iVar4);
        return 0;
      }
      if (__dest == piVar2 + -0x34) {
        if (*(int *)(iVar3 + 0x4b0) != 0) {
          *(undefined4 *)(*(int *)(iVar3 + 0x4b0) + 4) = *(undefined4 *)(iVar3 + 0x4b4);
        }
        if (*(undefined4 **)(iVar3 + 0x4b4) != (undefined4 *)0x0) {
          **(undefined4 **)(iVar3 + 0x4b4) = *(undefined4 *)(iVar3 + 0x4b0);
        }
        *(undefined4 *)(iVar3 + 0x4b0) = 0;
        *(undefined4 *)(iVar3 + 0x4b4) = 0;
        *(int *)(param_1 + 0xa7beec) = *(int *)(param_1 + 0xa7beec) + -1;
        goto LAB_00104d70;
      }
      piVar2 = (int *)*piVar2;
    } while( true );
  }
  _raw_spin_lock_bh(iVar4);
  piVar2 = *(int **)(param_1 + 0xa7bef0);
  do {
    if ((int *)(param_1 + 0xa7bef0) == piVar2) {
      piVar2 = *(int **)(param_1 + 0xa7bef4);
      iVar1 = *piVar2;
      *(int **)(iVar3 + 0x4b4) = piVar2;
      *(int *)(iVar3 + 0x4b0) = iVar1;
      *(int *)(*piVar2 + 4) = iVar3 + 0x4b0;
      *piVar2 = iVar3 + 0x4b0;
      *(int *)(iVar3 + 0x4ac) = iVar3;
      *(int *)(param_1 + 0xa7beec) = *(int *)(param_1 + 0xa7beec) + 1;
      _raw_spin_unlock_bh(iVar4);
LAB_00104cc0:
      local_20 = *(int *)(iVar3 + 4);
      local_1c = iVar3;
      mt_notify_call_chain(*(int *)(local_20 + 8) + 0xa7bef8,2,&local_20);
      return 0;
    }
    if (__dest == piVar2 + -0x34) {
      _raw_spin_unlock_bh(iVar4);
      if (2 < DebugLevel) {
        printk("%s(): STARec %d already exist\n","add_starec",*(undefined2 *)(iVar3 + 0x3e2));
      }
      goto LAB_00104cc0;
    }
    piVar2 = (int *)*piVar2;
  } while( true );
}

