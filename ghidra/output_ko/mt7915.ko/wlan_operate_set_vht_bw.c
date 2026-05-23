// module: mt7915.ko
// function: wlan_operate_set_vht_bw @ 0x10824c
// size: 164 bytes
//

undefined4 wlan_operate_set_vht_bw(int param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_21 [2];
  undefined1 local_1f;
  
  iVar3 = *(int *)(param_1 + 0xb14);
  uVar1 = wlan_config_get_vht_bw();
  if (*(byte *)(iVar3 + 0x52) == param_2) {
    uVar2 = 0;
  }
  else {
    if (uVar1 < param_2) {
      if (DebugLevel < 4) {
        uVar2 = 0xffffffff;
      }
      else {
        printk("%s(): new vht_bw:%d > cap_vht_bw: %d, correct to cap_vht_bw\n",
               "wlan_operate_set_vht_bw",param_2,uVar1);
        uVar2 = 0xffffffff;
      }
    }
    else {
      uVar2 = 0;
      uVar1 = param_2;
    }
    phy_freq_get_cfg(param_1,auStack_21);
    local_1f = (undefined1)uVar1;
    operate_loader_phy(param_1,auStack_21);
  }
  return uVar2;
}

