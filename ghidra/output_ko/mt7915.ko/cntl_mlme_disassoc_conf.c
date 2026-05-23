// module: mt7915.ko
// function: cntl_mlme_disassoc_conf @ 0x10ccf0
// size: 64 bytes
//

void cntl_mlme_disassoc_conf(undefined4 param_1,int param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(*(int *)(param_2 + 0x92c) + 0xe20) + 0x28);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0010cd08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(param_2);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: No cntl_disassoc_conf hook api.\n","cntl_mlme_disassoc_conf");
  return;
}

