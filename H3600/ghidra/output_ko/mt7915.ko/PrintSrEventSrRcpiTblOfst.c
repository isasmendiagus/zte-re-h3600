// module: mt7915.ko
// function: PrintSrEventSrRcpiTblOfst @ 0x17127c
// size: 56 bytes
//

void PrintSrEventSrRcpiTblOfst(int param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  FUN_0016b708();
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nu2RxBwRcpiOfst = %x, u2StbcRcpiOfst = %x, u2NumAntRcpiOfst = %x\nu2LdpcRcpiOfst = %x, u2DcmRcpiOfst  = %x, u2MacRcpiOfst    = %x\nu2SigRcpiOfst  = %x\n"
         ,"PrintSrRcpiTblOfst",*(undefined2 *)(param_1 + 0xc),*(undefined2 *)(param_1 + 0xe),
         *(undefined2 *)(param_1 + 0x10),*(undefined2 *)(param_1 + 0x12),
         *(undefined2 *)(param_1 + 0x14),*(undefined2 *)(param_1 + 0x16),
         *(undefined2 *)(param_1 + 0x18));
  return;
}

