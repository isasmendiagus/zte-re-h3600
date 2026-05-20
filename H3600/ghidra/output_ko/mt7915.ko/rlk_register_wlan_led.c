// module: mt7915.ko
// function: rlk_register_wlan_led @ 0x15fb18
// size: 76 bytes
//

void rlk_register_wlan_led(int param_1)

{
  undefined4 local_18;
  uint local_14;
  uint local_10;
  undefined4 local_c;
  
  local_c = 0;
  if (param_1 == 0) {
    local_10 = 0xf3f8;
  }
  else {
    local_10 = 0xf400;
  }
  local_18 = 0x5300;
  local_14 = (uint)(param_1 != 0);
  local_10 = local_10 | 0x150000;
  LedInstall50msBlink(&local_18);
  return;
}

