// module: mt7915.ko
// function: ShowSrNRTCtrl @ 0x16cae8
// size: 72 bytes
//

int ShowSrNRTCtrl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x29,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srnrtctrl=0\n","ShowSrNRTCtrl");
  }
  return iVar1;
}

