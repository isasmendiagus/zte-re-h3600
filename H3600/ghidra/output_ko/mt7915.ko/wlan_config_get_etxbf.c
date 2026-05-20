// module: mt7915.ko
// function: wlan_config_get_etxbf @ 0x106524
// size: 12 bytes
//

undefined1 wlan_config_get_etxbf(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 10);
}

