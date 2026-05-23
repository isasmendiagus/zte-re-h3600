// module: mt7915.ko
// function: ShowSrQCtrl @ 0x16ca04
// size: 72 bytes
//

int ShowSrQCtrl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x26,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srqctrl=0\n","ShowSrQCtrl");
  }
  return iVar1;
}

