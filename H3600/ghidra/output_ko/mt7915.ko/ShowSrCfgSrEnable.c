// module: mt7915.ko
// function: ShowSrCfgSrEnable @ 0x16cb34
// size: 72 bytes
//

int ShowSrCfgSrEnable(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x2a,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsren=0\n","ShowSrCfgSrEnable");
  }
  return iVar1;
}

