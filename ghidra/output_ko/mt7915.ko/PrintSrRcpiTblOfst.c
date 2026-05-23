// module: mt7915.ko
// function: PrintSrRcpiTblOfst @ 0x16d3d0
// size: 24 bytes
//

void PrintSrRcpiTblOfst(undefined2 *param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nu2RxBwRcpiOfst = %x, u2StbcRcpiOfst = %x, u2NumAntRcpiOfst = %x\nu2LdpcRcpiOfst = %x, u2DcmRcpiOfst  = %x, u2MacRcpiOfst    = %x\nu2SigRcpiOfst  = %x\n"
         ,"PrintSrRcpiTblOfst",*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5],
         param_1[6]);
  return;
}

