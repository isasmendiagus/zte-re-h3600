// module: mt7915.ko
// function: ShowSrCfgTxcQueue @ 0x16ccb0
// size: 72 bytes
//

int ShowSrCfgTxcQueue(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x2f,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgtxcq=0\n","ShowSrCfgTxcQueue");
  }
  return iVar1;
}

