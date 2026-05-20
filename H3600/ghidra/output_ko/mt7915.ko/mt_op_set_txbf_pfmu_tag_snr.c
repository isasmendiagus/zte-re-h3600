// module: mt7915.ko
// function: mt_op_set_txbf_pfmu_tag_snr @ 0x259ea0
// size: 236 bytes
//

undefined4 mt_op_set_txbf_pfmu_tag_snr(int param_1,undefined1 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x158) != (code *)0x0) {
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x17,*param_2);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x18,param_2[1]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x19,param_2[2]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x1a,param_2[3]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x1b,param_2[4]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x1c,param_2[5]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x1d,param_2[6]);
    (**(code **)(iVar2 + 0x158))(*(undefined4 *)(iVar1 + 0xa797a0),0x1e,param_2[7]);
    return 0;
  }
  return 0x504;
}

