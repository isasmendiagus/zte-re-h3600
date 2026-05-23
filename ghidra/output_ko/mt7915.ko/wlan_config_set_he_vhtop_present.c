// module: mt7915.ko
// function: wlan_config_set_he_vhtop_present @ 0x206370
// size: 12 bytes
//

void wlan_config_set_he_vhtop_present(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x6a) = param_2;
  return;
}

