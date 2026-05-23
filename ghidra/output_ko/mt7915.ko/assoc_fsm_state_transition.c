// module: mt7915.ko
// function: assoc_fsm_state_transition @ 0x10c8fc
// size: 124 bytes
//

undefined4 assoc_fsm_state_transition(undefined4 *param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  iVar1 = DebugLevel;
  iVar3 = param_1[0x2f7];
  param_1[0x2f7] = param_2;
  if (1 < iVar1) {
    pcVar2 = "(STA)";
    if (param_1[5] == 0x100) {
      pcVar2 = "(REPT)";
    }
    printk("ASSOC[%s, TYPE:%d %s]: [%s] \t==============================================> [%s]\n",
           *param_1,param_1[5],pcVar2,*(undefined4 *)(ASSOC_FSM_STATE_STR + iVar3 * 4),
           *(undefined4 *)(ASSOC_FSM_STATE_STR + param_2 * 4));
  }
  return 1;
}

