// module: mt7915.ko
// function: hqa_mu_set_enable @ 0x935ec
// size: 256 bytes
//

undefined4 hqa_mu_set_enable(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Argument is NULL\n","hqa_mu_set_enable");
  }
  else {
    cVar1 = os_str_toul(param_2,0,10);
    if (0 < DebugLevel) {
      pcVar3 = "Enable";
      if (cVar1 != '\x01') {
        pcVar3 = "Disable";
      }
      printk("%s: MU %s %u\n","hqa_mu_set_enable",pcVar3,cVar1);
    }
    iVar2 = hqa_wifi_test_mu_set_enable(param_1,cVar1);
    if (iVar2 == 0) {
      if (DebugLevel < 1) {
        return 1;
      }
      uVar4 = 1;
      pcVar3 = "Success";
      goto LAB_000936c8;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  uVar4 = 0;
  pcVar3 = "Fail";
LAB_000936c8:
  printk("%s: CMD %s\n","hqa_mu_set_enable",pcVar3);
  return uVar4;
}

