// module: mt7915.ko
// function: wlan_operate_set_cen_ch_2 @ 0x1076d8
// size: 68 bytes
//

undefined4 wlan_operate_set_cen_ch_2(int param_1,uint param_2)

{
  undefined1 auStack_19 [5];
  undefined1 local_14;
  
  if (*(byte *)(*(int *)(param_1 + 0xb14) + 4) != param_2) {
    phy_freq_get_cfg(param_1,auStack_19);
    local_14 = (undefined1)param_2;
    operate_loader_phy(param_1,auStack_19);
  }
  return 0;
}

