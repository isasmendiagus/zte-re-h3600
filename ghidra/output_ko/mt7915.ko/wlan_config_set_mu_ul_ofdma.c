// module: mt7915.ko
// function: wlan_config_set_mu_ul_ofdma @ 0x2063dc
// size: 12 bytes
//

void wlan_config_set_mu_ul_ofdma(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0xd) = param_2;
  return;
}

