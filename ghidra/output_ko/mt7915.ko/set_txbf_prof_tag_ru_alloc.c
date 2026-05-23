// module: mt7915.ko
// function: set_txbf_prof_tag_ru_alloc @ 0xe7bdc
// size: 88 bytes
//

undefined4 set_txbf_prof_tag_ru_alloc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = os_str_tol(param_2,0,10);
  if (*(code **)(iVar2 + 0x158) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000e7c28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (**(code **)(iVar2 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x26,uVar1);
    return uVar3;
  }
  return 0;
}

