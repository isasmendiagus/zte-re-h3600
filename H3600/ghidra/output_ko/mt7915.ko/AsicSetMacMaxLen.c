// module: mt7915.ko
// function: AsicSetMacMaxLen @ 0x133518
// size: 68 bytes
//

undefined4 AsicSetMacMaxLen(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xac) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00133548. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0xac))();
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicSetMacMaxLen");
  return 0;
}

