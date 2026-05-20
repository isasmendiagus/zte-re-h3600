// module: mt7915.ko
// function: SetSrCfgTxcQueue @ 0x16c544
// size: 72 bytes
//

int SetSrCfgTxcQueue(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x14,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgtxcq=1\n","SetSrCfgTxcQueue");
  }
  return iVar1;
}

