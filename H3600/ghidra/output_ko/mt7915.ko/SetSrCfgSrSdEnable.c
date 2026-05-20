// module: mt7915.ko
// function: SetSrCfgSrSdEnable @ 0x16c414
// size: 72 bytes
//

int SetSrCfgSrSdEnable(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x10,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsrsden=1\n","SetSrCfgSrSdEnable");
  }
  return iVar1;
}

