// module: mt7915.ko
// function: Set_TxBfProfileTag_SmartAnt @ 0xe7864
// size: 84 bytes
//

undefined4 Set_TxBfProfileTag_SmartAnt(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar2 = os_str_tol(param_2,0,10);
  if (*(code **)(iVar1 + 0x158) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000e78ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x1f,uVar2);
    return uVar2;
  }
  return 0;
}

