// module: mt7915.ko
// function: ShowSrInd @ 0x16c8d4
// size: 72 bytes
//

int ShowSrInd(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x22,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srind=0\n","ShowSrInd");
  }
  return iVar1;
}

