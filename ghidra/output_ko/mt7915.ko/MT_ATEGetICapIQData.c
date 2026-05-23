// module: mt7915.ko
// function: MT_ATEGetICapIQData @ 0x27f9c0
// size: 176 bytes
//

undefined4 MT_ATEGetICapIQData(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  code *UNRECOVERED_JUMPTABLE;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk(&_LC65,"MT_ATEGetICapIQData");
  }
  UNRECOVERED_JUMPTABLE = *(code **)(iVar1 + 0x198);
  if ((UNRECOVERED_JUMPTABLE == (code *)0x0) &&
     (UNRECOVERED_JUMPTABLE = *(code **)(iVar1 + 0x194), UNRECOVERED_JUMPTABLE == (code *)0x0)) {
    if (-1 < DebugLevel) {
      printk("%s : The function is not hooked !!\n","MT_ATEGetICapIQData");
    }
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x0027fa24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (*UNRECOVERED_JUMPTABLE)(param_1,param_2,param_3,param_4);
  return uVar2;
}

