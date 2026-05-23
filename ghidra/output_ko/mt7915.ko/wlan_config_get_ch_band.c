// module: mt7915.ko
// function: wlan_config_get_ch_band @ 0x1064e4
// size: 12 bytes
//

undefined1 wlan_config_get_ch_band(int param_1)

{
  return **(undefined1 **)(param_1 + 0xb10);
}

