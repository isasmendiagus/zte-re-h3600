// module: mt7915.ko
// function: ShowSrCfgSrPeriodThr @ 0x16cde0
// size: 72 bytes
//

int ShowSrCfgSrPeriodThr(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x33,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsrperiodthr=0\n","ShowSrCfgSrPeriodThr");
  }
  return iVar1;
}

