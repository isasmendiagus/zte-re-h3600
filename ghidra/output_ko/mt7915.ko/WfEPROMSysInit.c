// module: mt7915.ko
// function: WfEPROMSysInit @ 0x13a25c
// size: 180 bytes
//

undefined4 WfEPROMSysInit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  RtmpChipOpsEepromHook(param_1,*(undefined4 *)(param_1 + 0x286280),0,param_1 + 0x286000,param_4);
  NICReadEEPROMParameters(param_1,mac);
  hc_radio_init(param_1,"rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e],
                *(undefined1 *)(param_1 + 0x79504d));
  uVar1 = HcGetRadioRfIC(param_1);
  if (2 < DebugLevel) {
    printk("%s():PhyCtrl=>RfIcType/rf_band_cap = 0x%x/0x%x\n","WfEPROMSysInit",
           "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e],uVar1);
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x88) != (code *)0x0) {
    (**(code **)(iVar2 + 0x88))(param_1);
  }
  return 0;
}

