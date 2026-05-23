// module: mt7915.ko
// function: PrintSrCmdSrQCtrl @ 0x16fd78
// size: 116 bytes
//

void PrintSrCmdSrQCtrl(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  if (0 < DebugLevel) {
    FUN_0016b3c0();
  }
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

