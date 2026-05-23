// module: mt7915.ko
// function: ShowSrCfgTxcQid @ 0x16ccfc
// size: 72 bytes
//

int ShowSrCfgTxcQid(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x30,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgtxcqid=0\n","ShowSrCfgTxcQid");
  }
  return iVar1;
}

