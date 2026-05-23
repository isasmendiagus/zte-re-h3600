// module: mt7915.ko
// function: vht80_channel_group @ 0x203818
// size: 132 bytes
//

undefined4 vht80_channel_group(undefined4 param_1,uint param_2,undefined4 param_3)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  
  uVar2 = wlan_config_get_ch_band(param_3);
  if (uVar2 < 2) {
    pbVar3 = &_LANCHOR1;
  }
  else {
    pbVar3 = &DAT_005dfe6c;
    if (uVar2 != 2) {
      pbVar3 = (byte *)0x0;
    }
  }
  uVar2 = (uint)pbVar3[1];
  if (uVar2 != 0) {
    bVar1 = *pbVar3;
    while( true ) {
      if (param_2 <= uVar2 && bVar1 <= param_2) {
        return 1;
      }
      uVar2 = (uint)pbVar3[4];
      if (uVar2 == 0) break;
      bVar1 = pbVar3[3];
      pbVar3 = pbVar3 + 3;
    }
    return 0;
  }
  return 0;
}

