// module: mt7915.ko
// function: wlan_config_set_edca_valid @ 0x106688
// size: 16 bytes
//

void wlan_config_set_edca_valid(int param_1,undefined1 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x36) = param_2;
  }
  return;
}

