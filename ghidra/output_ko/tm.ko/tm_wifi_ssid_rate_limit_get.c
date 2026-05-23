// module: tm.ko
// function: tm_wifi_ssid_rate_limit_get @ 0x51ae8
// size: 160 bytes
//

undefined4 tm_wifi_ssid_rate_limit_get(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  bool bVar2;
  int local_24;
  uint local_20;
  uint uStack_1c;
  
  local_24 = 0;
  local_20 = 0;
  uStack_1c = 0;
  iVar1 = sadm_get_indtbl_flow_tfcfg_table(param_1,1,&local_24);
  if (iVar1 == 0) {
    *(bool *)param_2 = local_24 != 0;
    iVar1 = sadm_get_indtbl_token_bucket_fill_spd(param_1,1,&local_20);
    if (iVar1 == 0) {
      if ((local_20 & 1) != 0) {
        bVar2 = 0xfffffffe < local_20;
        local_20 = local_20 + 1;
        uStack_1c = uStack_1c + bVar2;
      }
      *param_3 = local_20;
      param_3[1] = uStack_1c;
      return 0;
    }
  }
  printk("tm_wifi_ssid_rate_limit_get fail\n");
  return 0xffffffff;
}

