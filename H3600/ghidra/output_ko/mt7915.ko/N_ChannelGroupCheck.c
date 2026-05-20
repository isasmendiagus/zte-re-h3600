// module: mt7915.ko
// function: N_ChannelGroupCheck @ 0x14116c
// size: 148 bytes
//

uint N_ChannelGroupCheck(undefined4 param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = wlan_config_get_ch_band(param_3);
  if (uVar1 != 0) {
    if (2 < uVar1) {
      return 0;
    }
    uVar1 = vht40_channel_group(param_1,param_2,param_3);
    return uVar1;
  }
  if (param_2 == 0xe) {
    return 0;
  }
  iVar2 = FUN_00140ed0(param_1,param_2 + 4U & 0xff,param_3);
  if (iVar2 != 0) {
    return 1;
  }
  iVar2 = FUN_00140ed0(param_1,param_2 - 4U & ~((int)(param_2 - 4U) >> 0x1f) & 0xff,param_3);
  return (uint)(iVar2 != 0);
}

