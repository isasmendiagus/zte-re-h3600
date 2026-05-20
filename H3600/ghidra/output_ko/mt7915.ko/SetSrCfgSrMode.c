// module: mt7915.ko
// function: SetSrCfgSrMode @ 0x16c4f8
// size: 72 bytes
//

int SetSrCfgSrMode(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x13,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsrmode=1\n","SetSrCfgSrMode");
  }
  return iVar1;
}

