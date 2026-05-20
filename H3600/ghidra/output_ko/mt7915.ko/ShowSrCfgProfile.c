// module: mt7915.ko
// function: ShowSrCfgProfile @ 0x16cf10
// size: 72 bytes
//

int ShowSrCfgProfile(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x37,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srcfgsrprofile=0\n","ShowSrCfgProfile");
  }
  return iVar1;
}

