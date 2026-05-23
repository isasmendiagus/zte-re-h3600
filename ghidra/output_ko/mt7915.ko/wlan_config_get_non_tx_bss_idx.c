// module: mt7915.ko
// function: wlan_config_get_non_tx_bss_idx @ 0x206540
// size: 12 bytes
//

undefined1 wlan_config_get_non_tx_bss_idx(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x75);
}

