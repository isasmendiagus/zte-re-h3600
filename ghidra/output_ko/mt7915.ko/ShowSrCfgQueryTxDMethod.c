// module: mt7915.ko
// function: ShowSrCfgQueryTxDMethod @ 0x16ce2c
// size: 72 bytes
//

int ShowSrCfgQueryTxDMethod(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x34,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsrquerytxd=0\n","ShowSrCfgQueryTxDMethod");
  }
  return iVar1;
}

