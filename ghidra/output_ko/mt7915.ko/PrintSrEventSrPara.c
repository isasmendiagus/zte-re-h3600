// module: mt7915.ko
// function: PrintSrEventSrPara @ 0x17116c
// size: 56 bytes
//

void PrintSrEventSrPara(int param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  FUN_0016b708();
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nu1NonSrgPdThr   = %x, u1SrgPdThr        = %x, u1PeriodOfst   = %x\nu1RcpiSourceSel = %x, u2ObssPdMin       = %x, u2ObssPdMinSrg = %x\neRespTxPwrMode  = %x, eTxPwrRestricMode = %x, u1ObssTxPwrRef = %x\n"
         ,"PrintSrPara",*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd),
         *(undefined1 *)(param_1 + 0xe),*(undefined1 *)(param_1 + 0xf),
         *(undefined2 *)(param_1 + 0x10),*(undefined2 *)(param_1 + 0x12),
         *(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),
         *(undefined1 *)(param_1 + 0x1c));
  return;
}

