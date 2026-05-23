// module: mt7915.ko
// function: AsicGetDbdcCtrl @ 0x13544c
// size: 76 bytes
//

undefined4 AsicGetDbdcCtrl(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x134) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00135484. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x134))(param_1,param_2);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicGetDbdcCtrl");
  return 0;
}

