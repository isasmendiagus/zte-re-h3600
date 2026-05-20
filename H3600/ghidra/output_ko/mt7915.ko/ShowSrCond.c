// module: mt7915.ko
// function: ShowSrCond @ 0x16c920
// size: 72 bytes
//

int ShowSrCond(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x23,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcond=0\n","ShowSrCond");
  }
  return iVar1;
}

