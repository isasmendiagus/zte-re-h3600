// module: mt7915.ko
// function: cntl_mlme_connect @ 0x10cf98
// size: 64 bytes
//

void cntl_mlme_connect(undefined4 param_1,int param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(*(int *)(param_2 + 0x92c) + 0xe20) + 4);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0010cfb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(*(int *)(param_2 + 0x92c),param_2,*(undefined4 *)(param_2 + 0x908));
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: No cntl_connect_proc hook api.\n","cntl_mlme_connect");
  return;
}

