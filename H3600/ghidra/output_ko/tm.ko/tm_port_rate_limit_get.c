// module: tm.ko
// function: tm_port_rate_limit_get @ 0x46bf0
// size: 132 bytes
//

undefined4 tm_port_rate_limit_get(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  int local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  local_24 = 0;
  local_20 = 0;
  uStack_1c = 0;
  iVar1 = sadm_get_indtbl_flow_tfcfg_table(param_1,0,&local_24);
  if (iVar1 == 0) {
    *(bool *)param_2 = local_24 != 0;
    iVar1 = sadm_get_indtbl_token_bucket_fill_spd(param_1,0,&local_20);
    if (iVar1 == 0) {
      *param_3 = local_20;
      param_3[1] = uStack_1c;
      return 0;
    }
  }
  printk("tm_port_rate_limit_get fail\n");
  return 0xffffffff;
}

