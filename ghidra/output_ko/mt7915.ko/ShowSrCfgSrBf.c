// module: mt7915.ko
// function: ShowSrCfgSrBf @ 0x16cbcc
// size: 72 bytes
//

int ShowSrCfgSrBf(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x2c,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsrbf=0\n","ShowSrCfgSrBf");
  }
  return iVar1;
}

