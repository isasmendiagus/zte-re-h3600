// module: mt7915.ko
// function: wlan_config_set_ba_txrx_wsize @ 0x106748
// size: 44 bytes
//

void wlan_config_set_ba_txrx_wsize(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xb10);
  if (0xff < param_2 - 1U) {
    param_2 = 0x40;
  }
  if (0xff < param_3 - 1U) {
    param_3 = 0x40;
  }
  if (iVar1 != 0) {
    *(short *)(iVar1 + 0x32) = (short)param_2;
    *(short *)(iVar1 + 0x34) = (short)param_3;
  }
  return;
}

