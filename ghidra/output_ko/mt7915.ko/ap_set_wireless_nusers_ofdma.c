// module: mt7915.ko
// function: ap_set_wireless_nusers_ofdma @ 0xcec4c
// size: 176 bytes
//

void ap_set_wireless_nusers_ofdma(undefined4 param_1,int param_2)

{
  uint uVar1;
  char acStack_26 [26];
  
  if (param_2 == 0) {
    return;
  }
  uVar1 = wlan_config_get_ofdma_user_cnt(param_2);
  if (1 < uVar1) {
    SetMuruSuTx(param_1,&_LC11);
    sprintf(acStack_26,"%s:%d","dl_comm_user_cnt",uVar1);
    if (0 < DebugLevel) {
      printk("func:%s, cmd:%s\n","ap_set_wireless_nusers_ofdma",acStack_26);
    }
    set_muru_mudl_ack_policy(param_1,5);
    set_muru_manual_config(param_1,acStack_26);
    set_muru_manual_config(param_1,"update");
  }
  return;
}

