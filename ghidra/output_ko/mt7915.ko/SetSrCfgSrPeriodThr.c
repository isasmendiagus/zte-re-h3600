// module: mt7915.ko
// function: SetSrCfgSrPeriodThr @ 0x16c674
// size: 72 bytes
//

int SetSrCfgSrPeriodThr(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x18,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsrperiodthr=480\n","SetSrCfgSrPeriodThr");
  }
  return iVar1;
}

