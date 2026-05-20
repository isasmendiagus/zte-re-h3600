// module: mt7915.ko
// function: SetSrCfgSrBf @ 0x16c460
// size: 72 bytes
//

int SetSrCfgSrBf(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x11,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsrbf=1\n","SetSrCfgSrBf");
  }
  return iVar1;
}

