// module: mt7915.ko
// function: mt_op_set_ibf_phase_cal_init @ 0x2599b8
// size: 80 bytes
//

undefined4 mt_op_set_ibf_phase_cal_init(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x13c) != (code *)0x0) {
    (**(code **)(iVar2 + 0x13c))(iVar1);
    return 0;
  }
  return 0x504;
}

