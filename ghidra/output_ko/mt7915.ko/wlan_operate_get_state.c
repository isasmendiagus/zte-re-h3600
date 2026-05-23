// module: mt7915.ko
// function: wlan_operate_get_state @ 0x106d18
// size: 76 bytes
//

undefined1 wlan_operate_get_state(int param_1)

{
  if (*(int *)(param_1 + 0xb14) != 0) {
    return *(undefined1 *)(*(int *)(param_1 + 0xb14) + 0x6c);
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s : Can\'t find wlan operate for wdev.\n","wlan_operate_get_state");
  return 0;
}

