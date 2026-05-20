// module: mt7915.ko
// function: HQA_MUCalLQ @ 0x279e9c
// size: 524 bytes
//

undefined4 HQA_MUCalLQ(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int local_38;
  int local_34;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined2 local_28;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 uStack_23;
  undefined1 uStack_22;
  undefined1 uStack_21;
  undefined1 local_20;
  undefined1 uStack_1f;
  undefined1 uStack_1e;
  undefined1 uStack_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined2 local_1a;
  
  local_34 = param_3 + 0xc;
  local_38 = 0;
  os_zero_mem(&local_30,10);
  os_zero_mem(&local_26,0xe);
  FUN_00276034(1,4,&local_34,&local_38);
  FUN_00276034(1,1,&local_34,&local_26);
  FUN_00276034(1,1,&local_34,&local_25);
  FUN_00276034(1,1,&local_34,&local_24);
  FUN_00276034(1,1,&local_34,&uStack_23);
  FUN_00276034(1,1,&local_34,&uStack_22);
  FUN_00276034(1,1,&local_34,&uStack_21);
  FUN_00276034(1,1,&local_34,&local_20);
  FUN_00276034(1,1,&local_34,&uStack_1f);
  FUN_00276034(1,1,&local_34,&uStack_1e);
  FUN_00276034(1,1,&local_34,&uStack_1d);
  FUN_00276034(1,1,&local_34,&local_1c);
  FUN_00276034(1,1,&local_34,&local_1b);
  FUN_00276034(1,2,&local_34,&local_1a);
  local_30 = local_26;
  local_2f = local_25;
  local_2e = local_24;
  local_2d = local_20;
  local_2c = local_1c;
  local_2b = local_1b;
  local_28 = local_1a;
  if (0 < DebugLevel) {
    printk("%s: gid:%u, txer:%u spe_idx:%d\n","HQA_MUCalLQ",0,0,local_1b);
  }
  if (local_38 == 0) {
    uVar1 = hqa_wifi_test_su_cal_lq(param_1,&local_30);
  }
  else {
    uVar1 = hqa_wifi_test_mu_cal_lq(param_1,&local_26);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar1);
  return uVar1;
}

