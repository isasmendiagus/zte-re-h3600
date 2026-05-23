// module: mt7915.ko
// function: cntl_fsm_reset @ 0x10d818
// size: 124 bytes
//

void cntl_fsm_reset(undefined4 *param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  iVar1 = DebugLevel;
  iVar3 = param_1[0x32a];
  param_1[0x32a] = 0;
  if (iVar1 < 2) {
    return;
  }
  pcVar2 = "(STA)";
  if (param_1[5] == 0x100) {
    pcVar2 = "(REPT)";
  }
  printk("CNTL [%s, TYPE:%d %s]: [%s] \t==============================================> [%s] (by %s)\n"
         ,*param_1,param_1[5],pcVar2,*(undefined4 *)(CNTL_FSM_STATE_STR + iVar3 * 4),
         CNTL_FSM_STATE_STR._0_4_,"cntl_fsm_reset");
  return;
}

