// module: mt7915.ko
// function: wlan_config_get_mu_dl_mimo @ 0x206580
// size: 12 bytes
//

undefined1 wlan_config_get_mu_dl_mimo(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0xe);
}

