// module: mt7915.ko
// function: mt_op_set_txbf_pfmu_tag_sumu @ 0x259bc0
// size: 88 bytes
//

undefined4 mt_op_set_txbf_pfmu_tag_sumu(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x158) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00259c04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),3,param_2);
    return uVar3;
  }
  return 0x504;
}

