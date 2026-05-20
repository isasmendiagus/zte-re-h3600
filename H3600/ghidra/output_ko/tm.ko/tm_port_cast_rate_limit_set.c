// module: tm.ko
// function: tm_port_cast_rate_limit_set @ 0x515ac
// size: 276 bytes
//

undefined4
tm_port_cast_rate_limit_set
          (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 auStack_20 [4];
  uint local_1c;
  
  iVar1 = getPort(param_1,auStack_20);
  if ((iVar1 == 0) && (local_1c < 8)) {
    if (param_5 < 6) {
      uVar3 = *(undefined4 *)(CSWTCH_431 + param_5 * 4);
    }
    else {
      uVar3 = 3;
    }
    iVar1 = sadm_set_up_tf_mode(1);
    if (iVar1 == 0) {
      uVar4 = local_1c & 0xff;
      iVar1 = sadm_set_indtbl_flow_tfcfg_table(uVar4,uVar3,param_2 != 0);
      if (((iVar1 == 0) && (iVar1 = sadm_set_bucket_fill_time(0x1869), iVar1 == 0)) &&
         (iVar1 = sadm_set_indtbl_token_bucket_fill_spd(uVar4,uVar3,param_3,param_4), iVar1 == 0)) {
        uVar2 = tm_getFillcap(param_3);
        iVar1 = sadm_set_indtbl_token_bucket_capacity(uVar4,uVar3,uVar2);
        if (iVar1 == 0) {
          return 0;
        }
      }
      printk("tm_port_cast_rate_limit_set fail\n");
    }
    else {
      printk("tm_port_rate_limit_set fail\n");
    }
  }
  else {
    printk("tm_port_cast_rate_limit_set fail, error port %d\n",param_1);
  }
  return 0xffffffff;
}

