// module: mt7915.ko
// function: mt_op_set_txbf_pfmu_tag_mem @ 0x259cd8
// size: 240 bytes
//

undefined4
mt_op_set_txbf_pfmu_tag_mem(int param_1,undefined1 *param_2,undefined1 *param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  pcVar3 = *(code **)(iVar2 + 0x158);
  if (pcVar3 != (code *)0x0) {
    (*pcVar3)(*(undefined4 *)(iVar1 + 0xa797a0),5,*param_2,pcVar3,param_4);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),6,param_2[1]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),7,param_2[2]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),8,param_2[3]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),9,*param_3);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),10,param_3[1]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0xb,param_3[2]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0xc,param_3[3]);
    return 0;
  }
  return 0x504;
}

