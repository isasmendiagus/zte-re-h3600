// module: mt7915.ko
// function: SetSrCfgTxcPath @ 0x16c5dc
// size: 72 bytes
//

int SetSrCfgTxcPath(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x16,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgtxcpath=1\n","SetSrCfgTxcPath");
  }
  return iVar1;
}

