// module: mt7915.ko
// function: SetSrCfgAcMethod @ 0x16c628
// size: 72 bytes
//

int SetSrCfgAcMethod(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x17,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgac=0\n","SetSrCfgAcMethod");
  }
  return iVar1;
}

