// module: mt7915.ko
// function: cntl_mlme_error_handle @ 0x10cfdc
// size: 200 bytes
//

void cntl_mlme_error_handle(undefined4 param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)(param_2 + 0x92c);
  iVar2 = puVar3[0x388];
  if (1 < DebugLevel) {
    pcVar1 = "(REPT)";
    if (puVar3[5] != 0x100) {
      pcVar1 = "(STA)";
    }
    printk("%s [%s %s]: [%s][%s] ====================> ERR\n","cntl_mlme_error_handle",*puVar3,
           pcVar1,*(undefined4 *)(CNTL_FSM_STATE_STR + puVar3[0x32a] * 4),
           *(undefined4 *)(CNTL_FSM_MSG_STR + *(int *)(param_2 + 0x904) * 4));
  }
  if (*(code **)(iVar2 + 0x30) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0010d020. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar2 + 0x30))(param_2);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: No cntl_error_handle hook api.\n","cntl_mlme_error_handle");
  return;
}

