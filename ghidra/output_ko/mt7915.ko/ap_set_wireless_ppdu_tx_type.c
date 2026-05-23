// module: mt7915.ko
// function: ap_set_wireless_ppdu_tx_type @ 0xcf2f0
// size: 180 bytes
//

void ap_set_wireless_ppdu_tx_type(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_2 == 0) {
    return;
  }
  iVar2 = wlan_config_get_ppdu_tx_type(param_2);
  if (2 < DebugLevel) {
    printk("func:%s, val:%d\n","ap_set_wireless_ppdu_tx_type",iVar2);
  }
  if (iVar2 == 4) {
    return;
  }
  if (iVar2 == 0) {
    SetMuruSuTx(param_1,&_LC10);
    uVar1 = 0x3df4;
  }
  else {
    if (iVar2 != 1) {
      return;
    }
    SetMuruSuTx(param_1,&_LC11);
    uVar1 = 0x3e08;
  }
  set_muru_manual_config(param_1,uVar1 | 0x2d0000);
  set_muru_manual_config(param_1,"update");
  return;
}

