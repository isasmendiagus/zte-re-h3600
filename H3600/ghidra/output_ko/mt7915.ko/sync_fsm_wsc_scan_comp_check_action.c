// module: mt7915.ko
// function: sync_fsm_wsc_scan_comp_check_action @ 0x109950
// size: 56 bytes
//

void sync_fsm_wsc_scan_comp_check_action(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 0x92c);
  if ((*(int *)(iVar2 + 0x3bc8) == 2) && (iVar1 = FUN_00108b10(), iVar1 != 0)) {
    return;
  }
  cntl_scan_conf(iVar2,0);
  return;
}

