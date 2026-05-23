// module: mt7915.ko
// function: PrintSrNRTCtrl @ 0x16d444
// size: 24 bytes
//

void PrintSrNRTCtrl(undefined1 *param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrtEn       = %x, fgSrtSrpEn     = %x, fgSrtAddrOrderEn = %x\nu2SrtInRcpiTh = %x, u2SrtOutRcpiTh = %x, u2SrtUsedCntTh   = %x\n"
         ,"PrintSrNRTCtrl",*param_1,param_1[1],param_1[2],*(undefined2 *)(param_1 + 4),
         *(undefined2 *)(param_1 + 6),*(undefined2 *)(param_1 + 8));
  return;
}

