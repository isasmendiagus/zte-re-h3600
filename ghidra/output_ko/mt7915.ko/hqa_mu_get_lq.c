// module: mt7915.ko
// function: hqa_mu_get_lq @ 0x9203c
// size: 164 bytes
//

undefined4 hqa_mu_get_lq(undefined4 param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined1 auStack_58 [80];
  
  os_zero_mem(auStack_58,0x50);
  iVar1 = hqa_wifi_test_mu_get_lq(param_1,auStack_58);
  if (iVar1 == 0) {
    if (DebugLevel < 1) {
      return 1;
    }
    uVar3 = 1;
    pcVar2 = "Success";
  }
  else {
    if (DebugLevel < 1) {
      return 0;
    }
    uVar3 = 0;
    pcVar2 = "Fail";
  }
  printk("%s: CMD %s\n","hqa_mu_get_lq",pcVar2);
  return uVar3;
}

