// module: mt7915.ko
// function: PrintSrCmdSrCap @ 0x16dad8
// size: 180 bytes
//

void PrintSrCmdSrCap(int param_1)

{
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  
  if (0 < DebugLevel) {
    FUN_0016b3c0();
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrEn                 = %x, fgSrgEn              = %x, fgNonSrgEn              = %x\nfgSingleMdpuRtsctsEn   = %x, fgHdrDurEn           = %x, fgTxopDurEn             = %x\nfgNonSrgInterPpduPresv = %x, fgSrgInterPpduPresv  = %x, fgSrRemTimeEn           = %x\nfgProtInSrWinDis       = %x, fgTxCmdDlRateSelEn   = %x, fgAmpduTxCntEn          = %x\n"
         ,"PrintSrCap",*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd),
         *(undefined1 *)(param_1 + 0xe),*(undefined1 *)(param_1 + 0xf),
         *(undefined1 *)(param_1 + 0x10),*(undefined1 *)(param_1 + 0x11),
         *(undefined1 *)(param_1 + 0x12),*(undefined1 *)(param_1 + 0x13),
         *(undefined1 *)(param_1 + 0x14),*(undefined1 *)(param_1 + 0x15),
         *(undefined1 *)(param_1 + 0x16),*(undefined1 *)(param_1 + 0x17),unaff_r4,unaff_r5);
  return;
}

