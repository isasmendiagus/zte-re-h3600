// module: mt7915.ko
// function: SetSrCfgQueryTxDMethod @ 0x16c6c0
// size: 72 bytes
//

int SetSrCfgQueryTxDMethod(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x19,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsrquerytxd=1\n","SetSrCfgQueryTxDMethod");
  }
  return iVar1;
}

