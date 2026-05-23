// module: mt7915.ko
// function: wlan_config_get_mmps @ 0x10690c
// size: 36 bytes
//

undefined1 wlan_config_get_mmps(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb10) != 0)) {
    return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x2e);
  }
  return 3;
}

