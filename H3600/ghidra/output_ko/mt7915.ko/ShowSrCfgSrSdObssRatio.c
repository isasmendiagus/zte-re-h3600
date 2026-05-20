// module: mt7915.ko
// function: ShowSrCfgSrSdObssRatio @ 0x16cec4
// size: 72 bytes
//

int ShowSrCfgSrSdObssRatio(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x36,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsrsdobss=0\n","ShowSrCfgSrSdObssRatio");
  }
  return iVar1;
}

