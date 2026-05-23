// module: mt7915.ko
// function: mt_op_set_txbf_pfmu_tag_matrix @ 0x259dc8
// size: 216 bytes
//

undefined4
mt_op_set_txbf_pfmu_tag_matrix
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5,
          undefined1 param_6,undefined1 param_7)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  undefined4 uVar4;
  
  uVar4 = param_4;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  pcVar3 = *(code **)(iVar2 + 0x158);
  if (pcVar3 != (code *)0x0) {
    (*pcVar3)(*(undefined4 *)(iVar1 + 0xa797a0),0xe,param_2,pcVar3,uVar4);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0xf,param_3);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x10,param_4);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x11,param_5);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x12,param_6);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x13,param_7);
    return 0;
  }
  return 0x504;
}

