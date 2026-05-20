// module: mt7915.ko
// function: wlan_config_set_mu_dl_mimo @ 0x2063e8
// size: 12 bytes
//

void wlan_config_set_mu_dl_mimo(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0xe) = param_2;
  return;
}

