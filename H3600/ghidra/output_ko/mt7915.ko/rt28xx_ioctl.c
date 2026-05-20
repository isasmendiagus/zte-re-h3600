// module: mt7915.ko
// function: rt28xx_ioctl @ 0x24608c
// size: 128 bytes
//

undefined4 rt28xx_ioctl(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  code *UNRECOVERED_JUMPTABLE;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (((iVar1 != 0) && (iVar1 = RtmpOsGetNetDevWdev(param_1), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x904), iVar1 != 0)) {
    UNRECOVERED_JUMPTABLE = *(code **)(iVar1 + 0xc0);
    if (UNRECOVERED_JUMPTABLE == (code *)0x0) {
      printk(&_LC6,0x334);
      dump_stack();
      UNRECOVERED_JUMPTABLE = *(code **)(iVar1 + 0xc0);
      if (UNRECOVERED_JUMPTABLE == (code *)0x0) {
        return 0xffffff9c;
      }
    }
                    /* WARNING: Could not recover jumptable at 0x002460e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (*UNRECOVERED_JUMPTABLE)(param_1,param_2,param_3);
    return uVar2;
  }
  return 0xffffff9c;
}

