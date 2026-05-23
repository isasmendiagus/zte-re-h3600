// module: mt7915.ko
// function: net_ad_insert_test_log @ 0x25e40c
// size: 288 bytes
//

undefined4
net_ad_insert_test_log
          (undefined4 param_1,int param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  
  if (param_4 == 4) {
    iVar3 = *(int *)(param_2 + 8);
    _raw_spin_lock_bh(param_2);
    cVar1 = *(char *)(param_2 + 6);
    _raw_spin_unlock_bh(param_2);
    if (cVar1 != '\0') goto LAB_0025e508;
    if (*(int *)(param_2 + 8) + 1 == *(int *)(param_2 + 0xc)) {
      if (*(char *)(param_2 + 4) == '\0') goto LAB_0025e4e8;
      *(undefined1 *)(param_2 + 7) = 1;
    }
    _raw_spin_lock_bh(param_2);
    iVar3 = *(int *)(param_2 + 0x14) + iVar3 * 0x1c;
    if (iVar3 == 0) {
      _raw_spin_unlock_bh(param_2);
    }
    else {
      iVar3 = net_ad_insert_rdd_log(iVar3,param_3,param_5);
      _raw_spin_unlock_bh(param_2);
      if (iVar3 == 0) {
        iVar3 = *(int *)(param_2 + 8) + 1;
        *(int *)(param_2 + 8) = iVar3;
        if (iVar3 < *(int *)(param_2 + 0xc)) {
          return 0;
        }
        *(undefined4 *)(param_2 + 8) = 0;
        return 0;
      }
    }
  }
  else {
    printk("%s: Unknown log type %08x\n","net_ad_insert_test_log",param_4);
  }
LAB_0025e4e8:
  if (param_2 == 0) {
    uVar2 = 0xff;
  }
  else {
    uVar2 = *(undefined1 *)(param_2 + 4);
  }
  printk("[WARN]%s: overwritable:%x, log_type:%08x\n","net_ad_insert_test_log",uVar2,param_4);
LAB_0025e508:
  printk("%s: Log dumping\n","net_ad_insert_test_log");
  return 0x606;
}

