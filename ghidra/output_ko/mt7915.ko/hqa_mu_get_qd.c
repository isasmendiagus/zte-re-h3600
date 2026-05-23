// module: mt7915.ko
// function: hqa_mu_get_qd @ 0x93458
// size: 400 bytes
//

undefined4 hqa_mu_get_qd(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Argument is NULL\n","hqa_mu_get_qd");
      goto LAB_000934b0;
    }
LAB_000934b8:
    uVar1 = 0;
  }
  else {
    uVar1 = os_str_toul(param_2,0,10);
    if (0 < DebugLevel) {
      printk("%s: subcarrier_idx = %d\n","hqa_mu_get_qd",uVar1);
    }
    iVar2 = hqa_wifi_test_mu_get_qd(param_1,(int)(char)uVar1,&local_48);
    if (iVar2 == 0) {
      if ((DebugLevel < 1) || (printk("%s: MU_STRUCT_MU_QD\n","hqa_mu_get_qd"), DebugLevel < 1)) {
        return 1;
      }
      printk("qd_report[0~6] = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",local_48,uStack_44,uStack_40,
             local_3c,local_38,local_34,local_30);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("qd_report[7~13] = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",local_2c,uStack_28,uStack_24,
             local_20,local_1c,local_18,local_14);
      if (DebugLevel < 1) {
        return 1;
      }
      uVar1 = 1;
      pcVar3 = "Success";
    }
    else {
LAB_000934b0:
      if (DebugLevel < 1) goto LAB_000934b8;
      uVar1 = 0;
      pcVar3 = "Fail";
    }
    printk("%s: CMD %s\n","hqa_mu_get_qd",pcVar3);
  }
  return uVar1;
}

