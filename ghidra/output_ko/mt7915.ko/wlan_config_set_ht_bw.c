// module: mt7915.ko
// function: wlan_config_set_ht_bw @ 0x1065f0
// size: 16 bytes
//

void wlan_config_set_ht_bw(int param_1,undefined1 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x15) = param_2;
  }
  wlan_operate_set_support_ch_width_set();
  return;
}

