// module: mt7915.ko
// function: SetSrCfgTxcQid @ 0x16c590
// size: 72 bytes
//

int SetSrCfgTxcQid(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x15,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgtxcqid=86\n","SetSrCfgTxcQid");
  }
  return iVar1;
}

