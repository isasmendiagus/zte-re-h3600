// module: mt7915.ko
// function: rtmp_set_vht @ 0x201c60
// size: 56 bytes
//

void rtmp_set_vht(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  if (param_3 == 0) {
    return;
  }
  uVar1 = wlan_config_get_vht_bw(param_2);
  if (*(char *)(param_3 + 0x12) != '\0') {
    if (uVar1 < 4) {
      *(char *)(param_3 + 0x13) = (char)uVar1;
    }
    else {
      *(undefined1 *)(param_3 + 0x13) = 0;
    }
    return;
  }
  return;
}

