// module: mt7915.ko
// function: ap_set_wireless_bss_configs @ 0xcf6f0
// size: 92 bytes
//

void ap_set_wireless_bss_configs
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  set_ap_wireless(param_1,"ppdu_tx_type",param_2);
  set_ap_wireless(param_1,"ofdma",param_2);
  set_ap_wireless(param_1,"num_users_ofdma",param_2);
  set_ap_wireless(param_1,"non_tx_bss_idx",param_2,param_4);
  return;
}

