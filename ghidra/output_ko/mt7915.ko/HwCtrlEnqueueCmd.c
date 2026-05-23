// module: mt7915.ko
// function: HwCtrlEnqueueCmd @ 0xb2508
// size: 676 bytes
//

undefined4
HwCtrlEnqueueCmd(int param_1,undefined4 param_2,undefined4 param_3,char param_4,int param_5,
                void *param_6,size_t param_7,undefined4 param_8,undefined4 param_9,
                undefined4 param_10,undefined4 param_11)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *local_3c [2];
  
  local_3c[0] = (undefined4 *)0x0;
  if ((*(uint *)(param_1 + 0xa39f84) & 0x100) != 0) {
    if (2 < DebugLevel) {
      printk("--->%s - NIC is not exist!!\n","HwCtrlEnqueueCmd");
    }
    return 1;
  }
  uVar2 = os_alloc_mem(param_1,local_3c,0x40);
  if (local_3c[0] == (undefined4 *)0x0) {
    return 3;
  }
  __memzero(local_3c[0],0x40);
  local_3c[0][0xd] = 0;
  *(char *)(local_3c[0] + 4) = param_4;
  if (param_4 != '\0') {
    local_3c[0][5] = 0;
    __init_waitqueue_head(local_3c[0] + 6,"&x->wait",&txop0);
  }
  if (param_7 != 0) {
    uVar2 = os_alloc_mem(param_1,local_3c[0] + 2,param_7);
    if ((void *)local_3c[0][2] == (void *)0x0) {
      uVar2 = 3;
      goto LAB_000b2670;
    }
    os_move_mem((void *)local_3c[0][2],param_6,param_7);
    local_3c[0][3] = param_7;
  }
  iVar4 = param_1 + 0x285ca8;
  *local_3c[0] = param_2;
  local_3c[0][1] = param_3;
  local_3c[0][9] = param_8;
  local_3c[0][10] = param_9;
  local_3c[0][0xb] = param_10;
  local_3c[0][0xc] = param_11;
  os_kref_init(local_3c[0] + 0xe);
  _raw_spin_lock_bh(iVar4);
  if ((*(uint *)(param_1 + 0x285c98) < 0x100) && ((*(uint *)(param_1 + 0x285ca4) & 3) != 0)) {
    os_kref_get(local_3c[0] + 0xe);
    if (*(int *)(param_1 + 0x285c98) == 0) {
      *(undefined4 **)(param_1 + 0x285c9c) = local_3c[0];
    }
    else {
      *(undefined4 **)(*(int *)(param_1 + 0x285ca0) + 0x3c) = local_3c[0];
    }
    *(undefined4 **)(param_1 + 0x285ca0) = local_3c[0];
    local_3c[0][0xf] = 0;
    *(int *)(param_1 + 0x285c98) = *(int *)(param_1 + 0x285c98) + 1;
    _raw_spin_unlock_bh(iVar4);
    RtmpOsCmdUp(param_1 + 0x285cac);
    puVar1 = local_3c[0];
    if (param_4 != '\0') {
      if (param_5 == 0) {
        param_5 = 100;
      }
      uVar3 = RTMPMsecsToJiffies(param_5);
      iVar4 = wait_for_completion_timeout(puVar1 + 5,uVar3);
      if (iVar4 == 0) {
        if (-1 < DebugLevel) {
          printk("%s(): HwCtrl CmdTimeout, TYPE:%d,ID:%d!!\n","HwCtrlEnqueueCmd",*local_3c[0],
                 local_3c[0][1]);
        }
        uVar2 = 1;
        local_3c[0][9] = 0;
        local_3c[0][10] = 0;
      }
    }
  }
  else {
    uVar2 = 1;
    _raw_spin_unlock_bh(iVar4);
  }
LAB_000b2670:
  os_kref_put(local_3c[0] + 0xe,free_hwcmd);
  return uVar2;
}

