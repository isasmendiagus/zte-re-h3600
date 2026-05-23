// module: mt7915.ko
// function: wlan_config_set_rts_pkt_thld @ 0x106708
// size: 16 bytes
//

void wlan_config_set_rts_pkt_thld(int param_1,undefined1 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x24) = param_2;
  }
  return;
}

