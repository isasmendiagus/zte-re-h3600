// module: mt7915.ko
// function: wlan_config_get_he_tx_nss @ 0x2064f8
// size: 12 bytes
//

undefined1 wlan_config_get_he_tx_nss(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x6b);
}

