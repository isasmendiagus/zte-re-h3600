// module: mt7915.ko
// function: ShowSrCap @ 0x16c83c
// size: 72 bytes
//

int ShowSrCap(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x1f,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcap=0\n","ShowSrCap");
  }
  return iVar1;
}

