// module: mt7915.ko
// function: SetSrSrgBitmapRefresh @ 0x16c7f0
// size: 72 bytes
//

int SetSrSrgBitmapRefresh(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x1e,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srsrgbmrefresh=0\n","SetSrSrgBitmapRefresh");
  }
  return iVar1;
}

