// module: tm.ko
// function: tm_wifi_ssid_rate_limit_set @ 0x51a58
// size: 144 bytes
//

undefined4
tm_wifi_ssid_rate_limit_set(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = sadm_set_indtbl_flow_tfcfg_table(param_1,1,param_2 != 0);
  if (((iVar1 == 0) && (iVar1 = sadm_set_bucket_fill_time(0x1869), iVar1 == 0)) &&
     (iVar1 = sadm_set_indtbl_token_bucket_fill_spd(param_1,1,param_3,param_4), iVar1 == 0)) {
    uVar2 = tm_getFillcap(param_3);
    iVar1 = sadm_set_indtbl_token_bucket_capacity(param_1,1,uVar2);
    if (iVar1 == 0) {
      return 0;
    }
  }
  printk("tm_wifi_ssid_rate_limit_set fail\n");
  return 0xffffffff;
}

