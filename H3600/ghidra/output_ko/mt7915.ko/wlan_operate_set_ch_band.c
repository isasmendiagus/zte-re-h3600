// module: mt7915.ko
// function: wlan_operate_set_ch_band @ 0x10761c
// size: 52 bytes
//

undefined4 wlan_operate_set_ch_band(undefined4 param_1,undefined1 param_2)

{
  undefined1 local_19 [13];
  
  phy_freq_get_cfg(param_1,local_19);
  local_19[0] = param_2;
  operate_loader_phy(param_1,local_19);
  return 0;
}

