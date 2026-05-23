// module: mt7915.ko
// function: chip_cfg_dly_int @ 0x13752c
// size: 68 bytes
//

undefined4
chip_cfg_dly_int(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops();
  if (*(code **)(iVar1 + 0x1fc) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00137564. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x1fc))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  return 0;
}

