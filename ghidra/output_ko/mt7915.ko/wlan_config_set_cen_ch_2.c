// module: mt7915.ko
// function: wlan_config_set_cen_ch_2 @ 0x106408
// size: 12 bytes
//

void wlan_config_set_cen_ch_2(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 5) = param_2;
  return;
}

