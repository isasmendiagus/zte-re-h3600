// module: mt7915.ko
// function: ShowSrNRT @ 0x16ca9c
// size: 72 bytes
//

int ShowSrNRT(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x28,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srnrt=0\n","ShowSrNRT");
  }
  return iVar1;
}

