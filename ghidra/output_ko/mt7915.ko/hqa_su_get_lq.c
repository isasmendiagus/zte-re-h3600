// module: mt7915.ko
// function: hqa_su_get_lq @ 0x92410
// size: 272 bytes
//

undefined4 hqa_su_get_lq(undefined4 param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  os_zero_mem(&local_24);
  if (0 < DebugLevel) {
    printk(&_LC0,"hqa_su_get_lq");
  }
  iVar1 = hqa_wifi_test_su_get_lq(param_1,&local_24);
  if (iVar1 == 0) {
    if ((DebugLevel < 1) || (printk("%s: SU_STRUCT_LQ_REPORT\n","hqa_su_get_lq"), DebugLevel < 1)) {
      return 1;
    }
    printk("%s: lq_report[0~4] = 0x%x 0x%x 0x%x 0x%x 0x%x\n","hqa_su_get_lq",local_24,local_20,
           local_1c,local_18,local_14);
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
  printk("%s: CMD %s\n","hqa_su_get_lq",pcVar2);
  return uVar3;
}

