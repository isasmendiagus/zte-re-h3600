// module: mt7915.ko
// function: HQA_MUCalInitMCS @ 0x27a0ac
// size: 392 bytes
//

undefined4 HQA_MUCalInitMCS(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int local_24;
  undefined1 uStack_1e;
  undefined1 uStack_1d;
  undefined1 uStack_1c;
  undefined1 uStack_1b;
  undefined1 uStack_1a;
  undefined1 uStack_19;
  undefined1 uStack_18;
  undefined1 uStack_17;
  undefined1 uStack_16;
  undefined1 uStack_15;
  undefined1 uStack_14;
  undefined1 local_13;
  undefined1 auStack_12 [2];
  
  local_24 = param_3 + 0xc;
  os_zero_mem(&uStack_1e,0xe);
  FUN_00276034(1,1,&local_24,&uStack_1e);
  FUN_00276034(1,1,&local_24,&uStack_1d);
  FUN_00276034(1,1,&local_24,&uStack_1c);
  FUN_00276034(1,1,&local_24,&uStack_1b);
  FUN_00276034(1,1,&local_24,&uStack_1a);
  FUN_00276034(1,1,&local_24,&uStack_19);
  FUN_00276034(1,1,&local_24,&uStack_18);
  FUN_00276034(1,1,&local_24,&uStack_17);
  FUN_00276034(1,1,&local_24,&uStack_16);
  FUN_00276034(1,1,&local_24,&uStack_15);
  FUN_00276034(1,1,&local_24,&uStack_14);
  FUN_00276034(1,1,&local_24,&local_13);
  FUN_00276034(1,2,&local_24,auStack_12);
  uVar1 = hqa_wifi_test_mu_cal_init_mcs(param_1,&uStack_1e);
  if (0 < DebugLevel) {
    printk("%s: spe_idx:%d\n","HQA_MUCalInitMCS",local_13);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar1);
  return uVar1;
}

