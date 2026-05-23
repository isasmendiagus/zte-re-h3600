// module: mt7915.ko
// function: mt_op_get_rx_stat_comm @ 0x2590ac
// size: 136 bytes
//

undefined4 mt_op_get_rx_stat_comm(int param_1,undefined4 param_2,undefined4 param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  ushort local_34 [2];
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = chip_get_rx_stat_comm(iVar1,param_2,param_3,local_34);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
    *param_4 = (uint)local_34[0];
    param_4[1] = local_30;
    param_4[2] = local_2c;
    param_4[3] = local_28;
    param_4[4] = local_24;
    param_4[5] = local_20;
    param_4[6] = local_1c;
  }
  return uVar2;
}

