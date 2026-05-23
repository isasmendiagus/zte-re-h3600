// module: mt7915.ko
// function: Set_TxBfProfileTagWrite @ 0xe7d10
// size: 80 bytes
//

undefined4 Set_TxBfProfileTagWrite(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = os_str_tol(param_2,0,10);
  if (*(code **)(iVar2 + 0x15c) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000e7d54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (**(code **)(iVar2 + 0x15c))(*(undefined4 *)(param_1 + 0xa797a0),uVar1);
    return uVar3;
  }
  return 0;
}

