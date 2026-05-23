// module: mt7915.ko
// function: PrintSrIBPD @ 0x16d400
// size: 24 bytes
//

void PrintSrIBPD(undefined1 *param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nu1InterBssByHdrBssid = %x, u1InterBssByMu        = %x, u1InterBssByPbssColor = %x\nu1InterBssByPaid     = %x, u1InterBssByBssColor  = %x\n"
         ,"PrintSrIBPD",*param_1,param_1[1],param_1[2],param_1[3],param_1[4]);
                    /* WARNING: Could not recover jumptable at 0x0016b6b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

