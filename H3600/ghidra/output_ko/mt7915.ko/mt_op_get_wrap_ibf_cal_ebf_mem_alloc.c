// module: mt7915.ko
// function: mt_op_get_wrap_ibf_cal_ebf_mem_alloc @ 0x259c78
// size: 96 bytes
//

undefined4 mt_op_get_wrap_ibf_cal_ebf_mem_alloc(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x154) != (code *)0x0) {
    (**(code **)(iVar2 + 0x154))(iVar1,param_2,param_3);
    return 0;
  }
  return 0x504;
}

