// module: mt7915.ko
// function: wlan_config_get_ba_tx_wsize @ 0x106960
// size: 24 bytes
//

undefined2 wlan_config_get_ba_tx_wsize(int param_1)

{
  undefined2 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0xb10) != 0) {
    uVar1 = *(undefined2 *)(*(int *)(param_1 + 0xb10) + 0x32);
  }
  return uVar1;
}

