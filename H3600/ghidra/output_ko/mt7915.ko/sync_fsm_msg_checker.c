// module: mt7915.ko
// function: sync_fsm_msg_checker @ 0x10b6c4
// size: 432 bytes
//

undefined4 sync_fsm_msg_checker(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  
  puVar4 = *(undefined4 **)(param_2 + 0x92c);
  iVar1 = get_scan_ctrl_by_wdev(param_1,puVar4);
  if (puVar4 != (undefined4 *)0x0) {
    if (*(char *)(puVar4 + 0x2aa) == '\0') {
      if (((*(byte *)(param_1 + 0x286294) & 3) == 3) && (puVar4[5] == 2)) {
        isValidApCliIf(*(undefined1 *)((int)puVar4 + 0xe));
      }
    }
    else if ((((*(byte *)(param_1 + 0x286294) & 3) != 3) || (puVar4[5] != 2)) ||
            (iVar2 = isValidApCliIf(*(undefined1 *)((int)puVar4 + 0xe)), iVar2 != 0)) {
      return 0;
    }
  }
  if ((iVar1 != 0) && (*(char *)(iVar1 + 0x17c) == '\x01')) {
    puVar3 = (undefined1 *)get_scan_ctrl_by_wdev(puVar4[2],puVar4);
    iVar2 = *(int *)(puVar3 + 0x90);
    *(undefined4 *)(puVar3 + 0x90) = 0;
    if (*(undefined4 **)(puVar3 + 0xaf5d0) == (undefined4 *)0x0) {
      if (-1 < DebugLevel) {
        printk("ScanCtrl->ScanReqwdev is NULL\n");
      }
    }
    else if (1 < DebugLevel) {
      printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
             ,**(undefined4 **)(puVar3 + 0xaf5d0),puVar3[0x1c6],*puVar3,
             *(undefined4 *)(SYNC_FSM_STATE_STR + iVar2 * 4),SYNC_FSM_STATE_STR._0_4_);
    }
  }
  iVar2 = FUN_00108a00(puVar4,param_2);
  if ((iVar2 != 0) && (1 < DebugLevel)) {
    printk("%s [%s]: [%s][%s] ====================> state Recovery for CNTL\n",
           "sync_fsm_msg_checker",*puVar4,
           *(undefined4 *)(SYNC_FSM_STATE_STR + *(int *)(iVar1 + 0x90) * 4),
           *(undefined4 *)(SYNC_FSM_MSG_STR + *(int *)(param_2 + 0x904) * 4));
    return 1;
  }
  return 1;
}

