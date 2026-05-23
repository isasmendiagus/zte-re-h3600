// module: mt7915.ko
// function: AsicSetRxPath @ 0x134238
// size: 84 bytes
//

undefined4 AsicSetRxPath(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xf0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00134278. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0xf0))(param_1,param_2,param_3);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicSetRxPath");
  return 0;
}

