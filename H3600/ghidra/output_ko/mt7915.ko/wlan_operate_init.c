// module: mt7915.ko
// function: wlan_operate_init @ 0x106bac
// size: 260 bytes
//

void wlan_operate_init(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_19 [13];
  
  iVar2 = *(int *)(param_1 + 0xb14);
  if (iVar2 == 0) {
    if (2 < DebugLevel) {
      printk("%s : Can\'t find wlan operate for wdev.\n","wlan_operate_init");
    }
  }
  else {
    phy_oper_init(param_1,iVar2);
    ht_oper_init(param_1,iVar2 + 8);
    ht_op_status_init(param_1,iVar2 + 0x20);
    vht_oper_init(param_1,iVar2 + 0x52);
    he_oper_init(param_1,iVar2 + 0x5c);
    if (param_1 != 0) {
      uVar3 = *(undefined4 *)(param_1 + 8);
      iVar2 = CheckNonOccupancyChannel(uVar3,param_1,0);
      if (iVar2 == 0) {
        uVar1 = FirstChannel(uVar3,param_1);
        *(undefined1 *)(param_1 + 0x1a) = uVar1;
      }
      os_zero_mem(auStack_19,9);
      phy_freq_get_cfg(param_1,auStack_19);
      iVar2 = DfsBypassRadarStateCheck(param_1);
      if (iVar2 == 0) {
        RadarStateCheck(uVar3,param_1);
      }
      operate_loader_phy(param_1,auStack_19);
    }
    dump_ht_cap(param_1);
  }
  return;
}

