// module: mt7915.ko
// function: wlan_config_get_ack_policy @ 0x1064fc
// size: 16 bytes
//

undefined1 wlan_config_get_ack_policy(int param_1,int param_2)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + param_2 + 6);
}

