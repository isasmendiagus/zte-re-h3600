// module: mt7915.ko
// function: SetSrCfgSrSdObssRatio @ 0x16c758
// size: 72 bytes
//

int SetSrCfgSrSdObssRatio(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x1b,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsrsdobss=500\n","SetSrCfgSrSdObssRatio");
  }
  return iVar1;
}

