// module: mt7915.ko
// function: ap_set_wireless_sta_configs @ 0xcf6e0
// size: 16 bytes
//

void ap_set_wireless_sta_configs(undefined4 param_1,undefined4 param_2)

{
  set_ap_wireless(param_1,"mcs_fixedrate",param_2);
  return;
}

