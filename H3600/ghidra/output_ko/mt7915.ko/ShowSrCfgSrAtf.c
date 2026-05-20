// module: mt7915.ko
// function: ShowSrCfgSrAtf @ 0x16cc18
// size: 72 bytes
//

int ShowSrCfgSrAtf(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x2d,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsratf=0\n","ShowSrCfgSrAtf");
  }
  return iVar1;
}

