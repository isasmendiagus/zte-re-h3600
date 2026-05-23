// module: mt7915.ko
// function: AsicRemoveRepeaterEntry @ 0x1326e8
// size: 68 bytes
//

void AsicRemoveRepeaterEntry(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x58) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0013271c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x58))(param_1,param_2);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicRemoveRepeaterEntry");
  return;
}

