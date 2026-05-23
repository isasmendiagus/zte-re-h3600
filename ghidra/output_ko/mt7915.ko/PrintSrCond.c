// module: mt7915.ko
// function: PrintSrCond @ 0x16d348
// size: 24 bytes
//

void PrintSrCond(undefined1 *param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nfgSrRcpiCckRateEn = %x, fgSrMacRcpiRateEn = %x, fgSrRxvRcpiRateEn = %x\nfgSrRcpiHeRateEn  = %x, fgSrRcpiVhtRateEn = %x, fgSrRcpiHtRateEn  = %x\nfgSrRcpiLgRateEn  = %x, fgSrRxvEntry      = %x, fgSrPeriodLimitEn = %x\nu1SrPeriodLimit   = %x\n"
         ,"PrintSrCond",*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5],param_1[6],
         param_1[7],param_1[8],param_1[9]);
  return;
}

