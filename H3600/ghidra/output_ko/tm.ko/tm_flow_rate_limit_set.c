// module: tm.ko
// function: tm_flow_rate_limit_set @ 0x51770
// size: 248 bytes
//

undefined4 tm_flow_rate_limit_set(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = adm_set_bucket_fill_time(0x1869);
  if (iVar1 == 0) {
    uVar2 = tm_getFillcap(param_3);
    uVar3 = tm_getFillcap(param_4);
    iVar1 = adm_set_bucket_c(param_1,uVar2,(uint)(param_3 << 3) / 5,param_2 != 0,param_2 != 0);
    iVar4 = adm_set_bucket_e(param_1,uVar3,(uint)(param_4 << 3) / 5);
    if (iVar4 == 0 && iVar1 == 0) {
      iVar1 = adm_set_spend_byte_cfg(0x18);
      uVar2 = 0;
      if (iVar1 != 0) {
        printk("tm_flow_rate_limit_set spend byte cfg fail\n");
        uVar2 = 0xffffffff;
      }
    }
    else {
      printk("tm_flow_rate_limit_set bucket_capacity fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_flow_rate_limit_set bucket_fill_time fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

