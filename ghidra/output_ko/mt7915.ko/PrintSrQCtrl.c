// module: mt7915.ko
// function: PrintSrQCtrl @ 0x16d3e8
// size: 24 bytes
//

void PrintSrQCtrl(undefined1 *param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrRxRptEn = %x, fgSrCw = %x, fgSrSuspend = %x, u4SrBackOffMask = %x\n",
         "PrintSrQCtrl",*param_1,param_1[1],param_1[2],*(undefined4 *)(param_1 + 4));
                    /* WARNING: Could not recover jumptable at 0x0016b66c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

