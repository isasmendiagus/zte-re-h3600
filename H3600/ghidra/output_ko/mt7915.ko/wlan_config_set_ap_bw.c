// module: mt7915.ko
// function: wlan_config_set_ap_bw @ 0x106430
// size: 12 bytes
//

void wlan_config_set_ap_bw(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 1) = param_2;
  return;
}

