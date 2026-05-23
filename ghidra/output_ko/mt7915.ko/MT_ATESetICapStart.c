// module: mt7915.ko
// function: MT_ATESetICapStart @ 0x27fa74
// size: 140 bytes
//

undefined4 MT_ATESetICapStart(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk(&_LC65,"MT_ATESetICapStart");
  }
  if (*(code **)(iVar1 + 0x188) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0027fac0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x188))(param_1,param_2);
    return uVar2;
  }
  if (-1 < DebugLevel) {
    printk("%s : The function is not hooked !!\n","MT_ATESetICapStart");
  }
  return 0;
}

