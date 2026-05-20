// module: mt7915.ko
// function: cntl_fsm_state_transition @ 0x10d0a8
// size: 132 bytes
//

undefined4 cntl_fsm_state_transition(undefined4 *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  iVar1 = DebugLevel;
  iVar3 = param_1[0x32a];
  param_1[0x32a] = param_2;
  if (1 < iVar1) {
    pcVar2 = "(STA)";
    if (param_1[5] == 0x100) {
      pcVar2 = "(REPT)";
    }
    printk("CNTL [%s, TYPE:%d %s]: [%s] \t==============================================> [%s] (by %s)\n"
           ,*param_1,param_1[5],pcVar2,*(undefined4 *)(CNTL_FSM_STATE_STR + iVar3 * 4),
           *(undefined4 *)(CNTL_FSM_STATE_STR + param_2 * 4),param_3);
  }
  return 1;
}

