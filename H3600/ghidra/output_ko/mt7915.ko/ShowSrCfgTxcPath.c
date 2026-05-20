// module: mt7915.ko
// function: ShowSrCfgTxcPath @ 0x16cd48
// size: 72 bytes
//

int ShowSrCfgTxcPath(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x31,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgtxcpath=0\n","ShowSrCfgTxcPath");
  }
  return iVar1;
}

