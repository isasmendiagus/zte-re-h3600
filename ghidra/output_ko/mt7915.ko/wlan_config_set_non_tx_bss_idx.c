// module: mt7915.ko
// function: wlan_config_set_non_tx_bss_idx @ 0x206418
// size: 12 bytes
//

void wlan_config_set_non_tx_bss_idx(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x75) = param_2;
  return;
}

