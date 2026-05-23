// module: mt7915.ko
// function: PrintSrCmdSrNRTCtrl @ 0x170914
// size: 56 bytes
//

void PrintSrCmdSrNRTCtrl(int param_1)

{
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  if (0 < DebugLevel) {
    FUN_0016b3c0();
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrtEn       = %x, fgSrtSrpEn     = %x, fgSrtAddrOrderEn = %x\nu2SrtInRcpiTh = %x, u2SrtOutRcpiTh = %x, u2SrtUsedCntTh   = %x\n"
         ,"PrintSrNRTCtrl",*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd),
         *(undefined1 *)(param_1 + 0xe),*(undefined2 *)(param_1 + 0x10),
         *(undefined2 *)(param_1 + 0x12),*(undefined2 *)(param_1 + 0x14),unaff_r4,unaff_lr);
  return;
}

