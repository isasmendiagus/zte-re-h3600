// module: mt7915.ko
// function: wdev_do_linkdown @ 0x14e5e0
// size: 36 bytes
//

undefined4 wdev_do_linkdown(int param_1)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  if ((*(int *)(param_1 + 0x904) != 0) &&
     (UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(param_1 + 0x904) + 0xac),
     UNRECOVERED_JUMPTABLE != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0014e5f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*UNRECOVERED_JUMPTABLE)();
    return uVar1;
  }
  return 0;
}

