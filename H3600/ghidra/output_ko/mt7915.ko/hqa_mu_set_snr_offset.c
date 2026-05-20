// module: mt7915.ko
// function: hqa_mu_set_snr_offset @ 0x92524
// size: 232 bytes
//

undefined4 hqa_mu_set_snr_offset(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Argument is NULL\n","hqa_mu_set_snr_offset");
  }
  else {
    uVar1 = os_str_tol(param_2,0,10);
    if (0 < DebugLevel) {
      printk("%s: SNRoffset:0x%x\n","hqa_mu_set_snr_offset",uVar1);
    }
    iVar2 = hqa_wifi_test_snr_offset_set(param_1,uVar1);
    if (iVar2 == 0) {
      if (DebugLevel < 1) {
        return 1;
      }
      uVar4 = 1;
      pcVar3 = "Success";
      goto LAB_000925e8;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  uVar4 = 0;
  pcVar3 = "Fail";
LAB_000925e8:
  printk("%s: CMD %s\n","hqa_mu_set_snr_offset",pcVar3);
  return uVar4;
}

