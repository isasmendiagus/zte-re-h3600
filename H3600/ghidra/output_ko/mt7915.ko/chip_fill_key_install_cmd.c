// module: mt7915.ko
// function: chip_fill_key_install_cmd @ 0x1376d0
// size: 68 bytes
//

undefined4
chip_fill_key_install_cmd
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops();
  if (*(code **)(iVar1 + 0x294) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00137708. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x294))(param_2,param_3,param_4,param_5);
    return uVar2;
  }
  return 1;
}

