// module: mt7915.ko
// function: wlan_config_get_rts_pkt_thld @ 0x1068d0
// size: 36 bytes
//

undefined1 wlan_config_get_rts_pkt_thld(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb10) != 0)) {
    return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x24);
  }
  return 2;
}

