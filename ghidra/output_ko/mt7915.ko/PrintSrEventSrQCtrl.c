// module: mt7915.ko
// function: PrintSrEventSrQCtrl @ 0x1712b4
// size: 56 bytes
//

void PrintSrEventSrQCtrl(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  if (DebugLevel < 0) {
    return;
  }
  FUN_0016b708();
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrRxRptEn = %x, fgSrCw = %x, fgSrSuspend = %x, u4SrBackOffMask = %x\n",
         "PrintSrQCtrl",*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd),
         *(undefined1 *)(param_1 + 0xe),*(undefined4 *)(param_1 + 0x10));
                    /* WARNING: Could not recover jumptable at 0x0016b66c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

