// module: mt7915.ko
// function: wlan_operate_set_he_af @ 0x20615c
// size: 24 bytes
//

undefined4 wlan_operate_set_he_af(int param_1,undefined1 param_2)

{
  if (param_1 != 0 && *(int *)(param_1 + 0xb14) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xb14) + 0x68) = param_2;
  }
  return 0;
}

