// module: mt7915.ko
// function: mt_op_set_ibf_phase_cal_e2p_update @ 0x2598ec
// size: 200 bytes
//

undefined4
mt_op_set_ibf_phase_cal_e2p_update(int param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  if (*(int *)(iVar2 + 0x144) == 0) {
    if (-1 < DebugLevel) {
      printk("%s : The function is not hooked !!\n","mt_op_set_ibf_phase_cal_e2p_update");
      return 0x504;
    }
    return 0x504;
  }
  uVar3 = param_3 >> 4;
  if (uVar3 == 1) {
    *(undefined1 *)(iVar1 + 0xa78730) = 1;
  }
  *(undefined1 *)(iVar1 + 0xa7868c) = 0;
  if (uVar3 != 1) {
    if (uVar3 == 0) {
      *(undefined1 *)(iVar1 + 0xa78730) = 0;
    }
    else {
      if (uVar3 != 2) {
        uVar3 = 0;
      }
      *(char *)(iVar1 + 0xa78730) = (char)uVar3;
    }
  }
  (**(code **)(iVar2 + 0x144))(iVar1,param_2,param_3,param_4);
  return 0;
}

