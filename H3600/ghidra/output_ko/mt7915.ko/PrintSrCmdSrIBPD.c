// module: mt7915.ko
// function: PrintSrCmdSrIBPD @ 0x170174
// size: 56 bytes
//

void PrintSrCmdSrIBPD(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  if (0 < DebugLevel) {
    FUN_0016b3c0();
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nu1InterBssByHdrBssid = %x, u1InterBssByMu        = %x, u1InterBssByPbssColor = %x\nu1InterBssByPaid     = %x, u1InterBssByBssColor  = %x\n"
         ,"PrintSrIBPD",*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd),
         *(undefined1 *)(param_1 + 0xe),*(undefined1 *)(param_1 + 0xf),
         *(undefined1 *)(param_1 + 0x10));
                    /* WARNING: Could not recover jumptable at 0x0016b6b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

