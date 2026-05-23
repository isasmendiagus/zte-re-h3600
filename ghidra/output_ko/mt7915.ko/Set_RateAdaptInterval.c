// module: mt7915.ko
// function: Set_RateAdaptInterval @ 0xe9e98
// size: 312 bytes
//

undefined4 Set_RateAdaptInterval(int param_1,char *param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 auStack_21 [5];
  
  if (2 < DebugLevel) {
    printk("%s():%s\n","Set_RateAdaptInterval",param_2);
  }
  pcVar1 = strchr(param_2,0x3a);
  if (((pcVar1 != (char *)0x0) && (*pcVar1 = '\0', *param_2 != '\0')) && (pcVar1[1] != '\0')) {
    uVar2 = os_str_tol(param_2,0,10);
    uVar3 = os_str_tol(pcVar1 + 1,0,10);
    if (0 < DebugLevel) {
      printk("%s():Set RateAdaptation TimeInterval as(%d:%d) ms\n","Set_RateAdaptInterval",uVar2,
             uVar3);
    }
    _raw_spin_lock_bh(param_1 + 0x285c50);
    *(undefined4 *)(param_1 + 0x794b4c) = uVar2;
    *(undefined4 *)(param_1 + 0x794b50) = uVar3;
    if ((&DAT_0036b908)[param_1] == '\x01') {
      RTMPCancelTimer(param_1 + 0x36b8d4,auStack_21);
      (&DAT_0036b908)[param_1] = 0;
    }
    _raw_spin_unlock_bh(param_1 + 0x285c50);
    return 1;
  }
  return 0;
}

