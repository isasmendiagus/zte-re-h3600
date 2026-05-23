// module: mt7915.ko
// function: ShowSrCfgSrSdEnable @ 0x16cb80
// size: 72 bytes
//

int ShowSrCfgSrSdEnable(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x2b,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsrsden=0\n","ShowSrCfgSrSdEnable");
  }
  return iVar1;
}

