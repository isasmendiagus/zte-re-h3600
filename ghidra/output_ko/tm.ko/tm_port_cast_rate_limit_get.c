// module: tm.ko
// function: tm_port_cast_rate_limit_get @ 0x4f640
// size: 224 bytes
//

undefined4
tm_port_cast_rate_limit_get(undefined4 param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int local_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [4];
  uint local_1c;
  
  local_2c = 0;
  local_28 = 0;
  uStack_24 = 0;
  iVar1 = getPort(param_1,auStack_20);
  if ((iVar1 == 0) && (local_1c < 8)) {
    if (param_4 - 2U < 4) {
      uVar2 = *(undefined4 *)(CSWTCH_382 + (param_4 - 2U) * 4);
    }
    else {
      uVar2 = 3;
    }
    iVar1 = sadm_get_indtbl_flow_tfcfg_table(local_1c,uVar2,&local_2c);
    if (iVar1 == 0) {
      *(bool *)param_2 = local_2c != 0;
      iVar1 = sadm_get_indtbl_token_bucket_fill_spd(local_1c,uVar2,&local_28);
      if (iVar1 == 0) {
        *param_3 = local_28;
        param_3[1] = uStack_24;
        return 0;
      }
    }
    printk("tm_port_cast_rate_limit_get fail\n");
  }
  else {
    printk("tm_port_cast_rate_limit_get fail, error port %d\n",param_1);
  }
  return 0xffffffff;
}

