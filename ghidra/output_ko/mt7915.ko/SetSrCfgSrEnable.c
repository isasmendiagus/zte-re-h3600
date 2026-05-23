// module: mt7915.ko
// function: SetSrCfgSrEnable @ 0x16c3c8
// size: 72 bytes
//

int SetSrCfgSrEnable(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0xf,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsren=1\n","SetSrCfgSrEnable");
  }
  return iVar1;
}

