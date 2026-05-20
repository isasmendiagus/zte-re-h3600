// module: mt7915.ko
// function: mt_op_get_rx_stat_user @ 0x259048
// size: 100 bytes
//

undefined4
mt_op_get_rx_stat_user(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = chip_get_rx_stat_user(iVar1,param_2,param_3,&local_1c);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
    *param_4 = local_1c;
    param_4[1] = local_18;
    param_4[2] = local_14;
  }
  return uVar2;
}

