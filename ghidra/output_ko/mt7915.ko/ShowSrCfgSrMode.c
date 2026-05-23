// module: mt7915.ko
// function: ShowSrCfgSrMode @ 0x16cc64
// size: 72 bytes
//

int ShowSrCfgSrMode(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x2e,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsrmode=0\n","ShowSrCfgSrMode");
  }
  return iVar1;
}

