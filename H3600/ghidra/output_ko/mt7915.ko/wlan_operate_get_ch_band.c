// module: mt7915.ko
// function: wlan_operate_get_ch_band @ 0x107610
// size: 12 bytes
//

undefined1 wlan_operate_get_ch_band(int param_1)

{
  return **(undefined1 **)(param_1 + 0xb14);
}

