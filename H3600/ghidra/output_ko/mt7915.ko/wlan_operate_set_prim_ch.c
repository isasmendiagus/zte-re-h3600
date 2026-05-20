// module: mt7915.ko
// function: wlan_operate_set_prim_ch @ 0x107650
// size: 76 bytes
//

undefined4 wlan_operate_set_prim_ch(int param_1,undefined1 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 auStack_19 [4];
  undefined1 local_15;
  
  phy_freq_get_cfg(param_1,auStack_19);
  local_15 = param_2;
  operate_loader_phy(param_1,auStack_19);
  uVar2 = *(undefined4 *)(param_1 + 8);
  uVar1 = HcGetBandByWdev(param_1);
  ZTE_wlan_edcca_setting(uVar2,uVar1);
  return 0;
}

