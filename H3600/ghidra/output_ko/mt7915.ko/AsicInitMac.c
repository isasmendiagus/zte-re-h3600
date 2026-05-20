// module: mt7915.ko
// function: AsicInitMac @ 0x1353bc
// size: 60 bytes
//

void AsicInitMac(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xfc) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001353e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0xfc))();
    return;
  }
  AsicNotSupportFunc(param_1,"AsicInitMac");
  return;
}

