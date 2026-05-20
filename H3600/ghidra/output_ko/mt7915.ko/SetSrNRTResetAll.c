// module: mt7915.ko
// function: SetSrNRTResetAll @ 0x16c37c
// size: 72 bytes
//

int SetSrNRTResetAll(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0xd,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srnrtreset=0\n","SetSrNRTResetAll");
  }
  return iVar1;
}

