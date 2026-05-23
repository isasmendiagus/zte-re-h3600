// module: mt7915.ko
// function: wlan_config_set_ap_cen @ 0x10643c
// size: 12 bytes
//

void wlan_config_set_ap_cen(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 2) = param_2;
  return;
}

