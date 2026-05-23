// module: tm.ko
// function: tm_port_rate_limit_set @ 0x51508
// size: 164 bytes
//

undefined4 tm_port_rate_limit_set(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_3 == 0 && param_4 == 0) {
    param_2 = 0;
  }
  iVar2 = param_4;
  iVar1 = sadm_set_up_tf_mode(1);
  if ((((iVar1 == 0) &&
       (iVar1 = sadm_set_indtbl_flow_tfcfg_table(param_1,0,param_2 != 0), iVar1 == 0)) &&
      (iVar1 = sadm_set_bucket_fill_time(0x1869), iVar1 == 0)) &&
     (iVar2 = sadm_set_indtbl_token_bucket_fill_spd(param_1,0,param_3,param_4,iVar2), iVar2 == 0)) {
    uVar3 = tm_getFillcap(param_3);
    iVar2 = sadm_set_indtbl_token_bucket_capacity(param_1,0,uVar3);
    if (iVar2 == 0) {
      return 0;
    }
  }
  printk("tm_port_rate_limit_set fail\n");
  return 0xffffffff;
}

