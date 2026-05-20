// module: mt7915.ko
// function: PrintSrPara @ 0x16d0e0
// size: 24 bytes
//

void PrintSrPara(undefined1 *param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nu1NonSrgPdThr   = %x, u1SrgPdThr        = %x, u1PeriodOfst   = %x\nu1RcpiSourceSel = %x, u2ObssPdMin       = %x, u2ObssPdMinSrg = %x\neRespTxPwrMode  = %x, eTxPwrRestricMode = %x, u1ObssTxPwrRef = %x\n"
         ,"PrintSrPara",*param_1,param_1[1],param_1[2],param_1[3],*(undefined2 *)(param_1 + 4),
         *(undefined2 *)(param_1 + 6),*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
         param_1[0x10]);
  return;
}

