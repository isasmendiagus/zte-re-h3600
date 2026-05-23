// module: mt7915.ko
// function: wlan_config_get_ht_stbc @ 0x1067a4
// size: 24 bytes
//

undefined1 wlan_config_get_ht_stbc(int param_1)

{
  undefined1 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0xb10) != 0) {
    uVar1 = *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x16);
  }
  return uVar1;
}

