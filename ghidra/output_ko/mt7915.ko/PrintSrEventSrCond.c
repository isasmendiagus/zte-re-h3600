// module: mt7915.ko
// function: PrintSrEventSrCond @ 0x171218
// size: 56 bytes
//

void PrintSrEventSrCond(int param_1)

{
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  
  if (DebugLevel < 0) {
    return;
  }
  FUN_0016b708();
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrRcpiCckRateEn = %x, fgSrMacRcpiRateEn = %x, fgSrRxvRcpiRateEn = %x\nfgSrRcpiHeRateEn  = %x, fgSrRcpiVhtRateEn = %x, fgSrRcpiHtRateEn  = %x\nfgSrRcpiLgRateEn  = %x, fgSrRxvEntry      = %x, fgSrPeriodLimitEn = %x\nu1SrPeriodLimit   = %x\n"
         ,"PrintSrCond",*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd),
         *(undefined1 *)(param_1 + 0xe),*(undefined1 *)(param_1 + 0xf),
         *(undefined1 *)(param_1 + 0x10),*(undefined1 *)(param_1 + 0x11),
         *(undefined1 *)(param_1 + 0x12),*(undefined1 *)(param_1 + 0x13),
         *(undefined1 *)(param_1 + 0x14),*(undefined1 *)(param_1 + 0x15),unaff_r4,unaff_r5);
  return;
}

