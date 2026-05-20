// module: mt7915.ko
// function: ShowSrIBPD @ 0x16ca50
// size: 72 bytes
//

int ShowSrIBPD(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x27,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show sribpd=0\n","ShowSrIBPD");
  }
  return iVar1;
}

