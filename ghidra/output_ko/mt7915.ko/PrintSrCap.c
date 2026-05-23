// module: mt7915.ko
// function: PrintSrCap @ 0x16d0c8
// size: 24 bytes
//

void PrintSrCap(undefined1 *param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrEn                 = %x, fgSrgEn              = %x, fgNonSrgEn              = %x\nfgSingleMdpuRtsctsEn   = %x, fgHdrDurEn           = %x, fgTxopDurEn             = %x\nfgNonSrgInterPpduPresv = %x, fgSrgInterPpduPresv  = %x, fgSrRemTimeEn           = %x\nfgProtInSrWinDis       = %x, fgTxCmdDlRateSelEn   = %x, fgAmpduTxCntEn          = %x\n"
         ,"PrintSrCap",*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5],param_1[6],
         param_1[7],param_1[8],param_1[9],param_1[10],param_1[0xb]);
  return;
}

