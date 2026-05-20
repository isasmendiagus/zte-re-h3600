// module: mt7915.ko
// function: mt_op_get_rx_stat_band @ 0x258f0c
// size: 192 bytes
//

undefined4 mt_op_get_rx_stat_band(int param_1,undefined4 param_2,undefined4 param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  ushort local_48 [2];
  uint local_44;
  ushort local_40;
  ushort local_3e;
  ushort local_3c;
  ushort local_3a;
  ushort local_38;
  ushort local_36;
  ushort local_34;
  ushort local_32;
  ushort local_30;
  ushort local_2e;
  ushort local_2c;
  ushort local_2a;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = chip_get_rx_stat_band(iVar1,param_2,param_3,local_48);
    *param_4 = (uint)local_48[0];
    param_4[1] = local_44;
    param_4[0xd] = (uint)local_2a;
    uVar2 = 0x501;
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    param_4[2] = (uint)local_40;
    param_4[3] = (uint)local_3e;
    param_4[4] = (uint)local_3c;
    param_4[5] = (uint)local_3a;
    param_4[6] = (uint)local_38;
    param_4[7] = (uint)local_36;
    param_4[8] = (uint)local_34;
    param_4[9] = (uint)local_32;
    param_4[10] = (uint)local_30;
    param_4[0xb] = (uint)local_2e;
    param_4[0xc] = (uint)local_2c;
  }
  return uVar2;
}

