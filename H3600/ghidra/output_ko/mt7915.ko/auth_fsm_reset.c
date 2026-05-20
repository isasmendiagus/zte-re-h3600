// module: mt7915.ko
// function: auth_fsm_reset @ 0x10e3e4
// size: 124 bytes
//

void auth_fsm_reset(undefined4 *param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  iVar1 = DebugLevel;
  iVar3 = param_1[0x38c];
  param_1[0x38c] = 0;
  if (iVar1 < 2) {
    return;
  }
  pcVar2 = "(STA)";
  if (param_1[5] == 0x100) {
    pcVar2 = "(REPT)";
  }
  printk("AUTH [%s, TYPE:%d %s]: [%s] \t==============================================> [%s]  (by %s)\n"
         ,*param_1,param_1[5],pcVar2,*(undefined4 *)(AUTH_FSM_STATE_STR + iVar3 * 4),
         AUTH_FSM_STATE_STR._0_4_,"auth_fsm_reset");
  return;
}

