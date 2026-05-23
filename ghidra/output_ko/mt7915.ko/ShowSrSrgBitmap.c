// module: mt7915.ko
// function: ShowSrSrgBitmap @ 0x16cff4
// size: 72 bytes
//

int ShowSrSrgBitmap(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x3a,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srsrgbm=0\n","ShowSrSrgBitmap");
  }
  return iVar1;
}

