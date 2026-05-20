// module: mt7915.ko
// function: wlan_config_set_mu_ul_mimo @ 0x2063f4
// size: 12 bytes
//

void wlan_config_set_mu_ul_mimo(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0xf) = param_2;
  return;
}

