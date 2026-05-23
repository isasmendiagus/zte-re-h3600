// module: mt7915.ko
// function: wlan_config_set_mu_dl_ofdma @ 0x2063d0
// size: 12 bytes
//

void wlan_config_set_mu_dl_ofdma(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0xc) = param_2;
  return;
}

