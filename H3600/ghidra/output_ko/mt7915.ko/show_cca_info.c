// module: mt7915.ko
// function: show_cca_info @ 0xe1804
// size: 60 bytes
//

undefined4 show_cca_info(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x30) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000e1834. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x30))(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    return uVar2;
  }
  return 0;
}

