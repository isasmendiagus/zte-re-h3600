// module: mt7915.ko
// function: ShowSrCfgAcMethod @ 0x16cd94
// size: 72 bytes
//

int ShowSrCfgAcMethod(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x32,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgac=0\n","ShowSrCfgAcMethod");
  }
  return iVar1;
}

