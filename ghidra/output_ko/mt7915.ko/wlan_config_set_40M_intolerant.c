// module: mt7915.ko
// function: wlan_config_set_40M_intolerant @ 0x106668
// size: 16 bytes
//

void wlan_config_set_40M_intolerant(int param_1,undefined1 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x1c) = param_2;
  }
  return;
}

