// module: mt7915.ko
// function: SetSrCfgSrAtf @ 0x16c4ac
// size: 72 bytes
//

int SetSrCfgSrAtf(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x12,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsratf=1\n","SetSrCfgSrAtf");
  }
  return iVar1;
}

