// module: mt7915.ko
// function: ShowSrPara @ 0x16c888
// size: 72 bytes
//

int ShowSrPara(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x20,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srpara=0\n","ShowSrPara");
  }
  return iVar1;
}

