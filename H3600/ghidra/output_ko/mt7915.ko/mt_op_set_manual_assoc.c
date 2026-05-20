// module: mt7915.ko
// function: mt_op_set_manual_assoc @ 0x25a248
// size: 88 bytes
//

undefined4
mt_op_set_manual_assoc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_r2;
  code *pcVar3;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  pcVar3 = *(code **)(iVar2 + 0x178);
  if (pcVar3 != (code *)0x0) {
    (*pcVar3)(iVar1,param_2,extraout_r2,pcVar3,param_4);
    return 0;
  }
  return 0x504;
}

