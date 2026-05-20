// module: tm.ko
// function: tm_flow_rate_limit_get @ 0x4bb30
// size: 120 bytes
//

undefined4 tm_flow_rate_limit_get(undefined4 param_1,undefined4 param_2,uint *param_3,uint *param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 auStack_30 [8];
  undefined1 auStack_28 [4];
  int local_24;
  int local_1c;
  
  iVar2 = adm_get_bucket_c(param_1,auStack_28);
  iVar3 = adm_get_bucket_e(param_1,auStack_30);
  if (iVar3 == 0 && iVar2 == 0) {
    uVar1 = (uint)(local_24 * 5) >> 3;
    *(bool *)param_2 = local_1c != 0;
    *param_3 = uVar1;
    *param_4 = uVar1;
    uVar4 = 0;
  }
  else {
    printk("tm_flow_rate_limit_get fail\n");
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

