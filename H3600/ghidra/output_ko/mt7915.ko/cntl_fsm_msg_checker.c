// module: mt7915.ko
// function: cntl_fsm_msg_checker @ 0x10cb50
// size: 348 bytes
//

undefined4 cntl_fsm_msg_checker(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  
  puVar5 = *(undefined4 **)(param_2 + 0x92c);
  if (puVar5 == (undefined4 *)0x0) {
LAB_0010cc74:
    uVar1 = 0;
  }
  else {
    if (*(char *)(puVar5 + 0x2aa) == '\0') {
      if (((*(byte *)(param_1 + 0x286294) & 3) == 3) && (puVar5[5] == 2)) {
        isValidApCliIf(*(undefined1 *)((int)puVar5 + 0xe));
      }
    }
    else if ((((*(byte *)(param_1 + 0x286294) & 3) != 3) || (puVar5[5] != 2)) ||
            (iVar2 = isValidApCliIf(*(undefined1 *)((int)puVar5 + 0xe)), iVar2 != 0))
    goto LAB_0010cc74;
    if (DebugLevel < 0) {
      uVar1 = 1;
      puVar5[0x32a] = 0;
    }
    else {
      printk("%s [%s]: [%s][%s], CNTL reset & Msg Drop\n","cntl_fsm_msg_checker",*puVar5,
             *(undefined4 *)(CNTL_FSM_STATE_STR + puVar5[0x32a] * 4),
             *(undefined4 *)(CNTL_FSM_MSG_STR + *(int *)(param_2 + 0x904) * 4));
      iVar2 = DebugLevel;
      iVar3 = puVar5[0x32a];
      puVar5[0x32a] = 0;
      if (iVar2 < 2) {
        uVar1 = 1;
      }
      else {
        pcVar4 = "(STA)";
        if (puVar5[5] == 0x100) {
          pcVar4 = "(REPT)";
        }
        printk("CNTL [%s, TYPE:%d %s]: [%s] \t==============================================> [%s] (by %s)\n"
               ,*puVar5,puVar5[5],pcVar4,*(undefined4 *)(CNTL_FSM_STATE_STR + iVar3 * 4),
               CNTL_FSM_STATE_STR._0_4_,"cntl_fsm_msg_checker");
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

