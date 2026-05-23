// module: mt7915.ko
// function: hqa_mu_get_init_mcs @ 0x91364
// size: 320 bytes
//

undefined4 hqa_mu_get_init_mcs(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Argument is NULL\n","hqa_mu_get_init_mcs");
      goto LAB_000913c8;
    }
LAB_000913d0:
    uVar1 = 0;
  }
  else {
    uVar1 = os_str_toul(param_2,0,10);
    os_zero_mem(&local_20,0x10);
    if (0 < DebugLevel) {
      printk("%s: gid:%u\n","hqa_mu_get_init_mcs",uVar1);
    }
    iVar2 = hqa_wifi_test_mu_get_init_mcs(param_1,uVar1,&local_20);
    if (iVar2 == 0) {
      if (DebugLevel < 1) {
        return 1;
      }
      printk("%s: InitMCS0:%u InitMCS1:%u InitMCS2:%u InitMCS3:%u\n","hqa_mu_get_init_mcs",local_20,
             local_1c,local_18,local_14);
      if (DebugLevel < 1) {
        return 1;
      }
      uVar1 = 1;
      pcVar3 = "Success";
    }
    else {
LAB_000913c8:
      if (DebugLevel < 1) goto LAB_000913d0;
      uVar1 = 0;
      pcVar3 = "Fail";
    }
    printk("%s: CMD %s\n","hqa_mu_get_init_mcs",pcVar3);
  }
  return uVar1;
}

