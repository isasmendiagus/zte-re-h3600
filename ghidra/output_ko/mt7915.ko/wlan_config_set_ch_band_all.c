// module: mt7915.ko
// function: wlan_config_set_ch_band_all @ 0x1063d4
// size: 52 bytes
//

void wlan_config_set_ch_band_all(int param_1,uint param_2)

{
  undefined4 *puVar1;
  undefined1 uVar2;
  int iVar3;
  
  if ((param_2 & 0x100) == 0) {
    if ((param_2 & 0xb1) == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 2;
  }
  iVar3 = param_1 + 0x680;
  do {
    puVar1 = (undefined4 *)(param_1 + 8);
    param_1 = param_1 + 0x10;
    *(undefined1 *)*puVar1 = uVar2;
  } while (param_1 != iVar3);
  return;
}

