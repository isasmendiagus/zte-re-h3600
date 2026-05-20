// module: mt7915.ko
// function: wlan_config_set_ch_band @ 0x1063b0
// size: 36 bytes
//

void wlan_config_set_ch_band(int param_1,uint param_2)

{
  undefined1 uVar1;
  
  if ((param_2 & 0x100) == 0) {
    if ((param_2 & 0xb1) == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 2;
  }
  **(undefined1 **)(param_1 + 0xb10) = uVar1;
  return;
}

