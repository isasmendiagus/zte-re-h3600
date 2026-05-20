// module: mt7915.ko
// function: wlan_operate_set_ht_stbc @ 0x108060
// size: 32 bytes
//

undefined4 wlan_operate_set_ht_stbc(int param_1)

{
  if (param_1 != 0) {
    wlan_operate_update_ht_stbc();
    return 0;
  }
  return 0;
}

