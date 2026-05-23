// module: mt7915.ko
// function: ShowSrSd @ 0x16cfa8
// size: 72 bytes
//

int ShowSrSd(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x39,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srsd=0\n","ShowSrSd");
  }
  return iVar1;
}

