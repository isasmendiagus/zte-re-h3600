// module: mt7915.ko
// function: SetSrCfgSrSdCgRatio @ 0x16c70c
// size: 72 bytes
//

int SetSrCfgSrSdCgRatio(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x1a,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsrsdcg=800\n","SetSrCfgSrSdCgRatio");
  }
  return iVar1;
}

