// module: mt7915.ko
// function: mt_op_get_rx_stat_path @ 0x258fcc
// size: 124 bytes
//

undefined4 mt_op_get_rx_stat_path(int param_1,undefined4 param_2,undefined4 param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  ushort local_18;
  short local_16;
  char local_14;
  char local_13;
  char local_12;
  char local_11;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = chip_get_rx_stat_path(iVar1,param_2,param_3,&local_18);
    uVar2 = 0;
    if (iVar1 != 0) {
      uVar2 = 0x501;
    }
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    *param_4 = (uint)local_18;
    param_4[1] = (int)local_16;
    param_4[2] = (int)local_14;
    param_4[3] = (int)local_13;
    param_4[4] = (int)local_12;
    param_4[5] = (int)local_11;
  }
  return uVar2;
}

