// module: mt7915.ko
// function: ShowSrCnt @ 0x16cf5c
// size: 72 bytes
//

int ShowSrCnt(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x38,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcnt=0\n","ShowSrCnt");
  }
  return iVar1;
}

