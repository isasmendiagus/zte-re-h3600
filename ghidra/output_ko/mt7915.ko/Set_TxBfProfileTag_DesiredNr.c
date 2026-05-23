// module: mt7915.ko
// function: Set_TxBfProfileTag_DesiredNr @ 0xe7b84
// size: 88 bytes
//

undefined4 Set_TxBfProfileTag_DesiredNr(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = os_str_tol(param_2,0,10);
  if (*(code **)(iVar2 + 0x158) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000e7bd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (**(code **)(iVar2 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x24,uVar1);
    return uVar3;
  }
  return 0;
}

