// module: mt7915.ko
// function: hqa_mu_set_speedup_lq @ 0x926fc
// size: 232 bytes
//

undefined4 hqa_mu_set_speedup_lq(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Argument is NULL\n","hqa_mu_set_speedup_lq");
  }
  else {
    uVar1 = os_str_tol(param_2,0,10);
    if (0 < DebugLevel) {
      printk("%s: spdup_lq:0x%x\n","hqa_mu_set_speedup_lq",uVar1);
    }
    iVar2 = hqa_wifi_test_mu_speed_up_lq(param_1,uVar1);
    if (iVar2 == 0) {
      if (DebugLevel < 1) {
        return 1;
      }
      uVar1 = 1;
      pcVar3 = "Success";
      goto LAB_000927c0;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  uVar1 = 0;
  pcVar3 = "Fail";
LAB_000927c0:
  printk("%s: CMD %s\n","hqa_mu_set_speedup_lq",pcVar3);
  return uVar1;
}

