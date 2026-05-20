// module: mt7915.ko
// function: wlan_operate_set_state @ 0x106d68
// size: 80 bytes
//

undefined4
wlan_operate_set_state(int param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(int *)(param_1 + 0xb14) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xb14) + 0x6c) = param_2;
    return 0;
  }
  if (DebugLevel < 0) {
    return 0xff;
  }
  printk("%s : Can\'t find wlan operate for wdev.\n","wlan_operate_set_state",param_3,DebugLevel,
         param_4);
  return 0xff;
}

