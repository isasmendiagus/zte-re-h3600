// module: mt7915.ko
// function: wlan_config_set_he_ldpc @ 0x206364
// size: 12 bytes
//

void wlan_config_set_he_ldpc(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x67) = param_2;
  return;
}

