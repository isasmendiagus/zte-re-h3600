// module: mt7915.ko
// function: ShowSrCfgSrSdCgRatio @ 0x16ce78
// size: 72 bytes
//

int ShowSrCfgSrSdCgRatio(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x35,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsrsdcg=0\n","ShowSrCfgSrSdCgRatio");
  }
  return iVar1;
}

