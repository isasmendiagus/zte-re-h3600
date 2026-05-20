// module: mt7915.ko
// function: wlan_config_get_mu_ul_ofdma @ 0x206574
// size: 12 bytes
//

undefined1 wlan_config_get_mu_ul_ofdma(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0xd);
}

