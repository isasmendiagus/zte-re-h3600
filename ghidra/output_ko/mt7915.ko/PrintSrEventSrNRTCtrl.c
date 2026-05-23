// module: mt7915.ko
// function: PrintSrEventSrNRTCtrl @ 0x17137c
// size: 128 bytes
//

void PrintSrEventSrNRTCtrl(int param_1)

{
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  if (DebugLevel < 0) {
    return;
  }
  FUN_0016b708();
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrtEn       = %x, fgSrtSrpEn     = %x, fgSrtAddrOrderEn = %x\nu2SrtInRcpiTh = %x, u2SrtOutRcpiTh = %x, u2SrtUsedCntTh   = %x\n"
         ,"PrintSrNRTCtrl",*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd),
         *(undefined1 *)(param_1 + 0xe),*(undefined2 *)(param_1 + 0x10),
         *(undefined2 *)(param_1 + 0x12),*(undefined2 *)(param_1 + 0x14),unaff_r4,unaff_lr);
  return;
}

