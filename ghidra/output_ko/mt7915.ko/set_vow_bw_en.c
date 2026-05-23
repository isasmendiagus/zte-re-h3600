// module: mt7915.ko
// function: set_vow_bw_en @ 0x43e80
// size: 252 bytes
//

undefined4 set_vow_bw_en(int param_1,char *param_2)

{
  int iVar1;
  int local_1c [2];
  
  if ((*(uint *)(param_1 + 0xa797a8) & 2) == 0) {
    *(undefined1 *)(param_1 + 0xa7a2e8) = 0;
    return 0;
  }
  if ((param_2 != (char *)0x0) && (iVar1 = sscanf(param_2,"%u",local_1c), iVar1 != 0)) {
    *(char *)(param_1 + 0xa7a2e8) = (char)local_1c[0];
    iVar1 = vow_set_feature_all(param_1);
    if (DebugLevel < 0) {
      if (iVar1 == 0) {
LAB_00043f1c:
        *(bool *)(param_1 + 0xa7a2fc) = local_1c[0] != 0;
        vow_set_at_estimator(param_1,1);
        return 1;
      }
    }
    else {
      printk("%s: set %u.\n","set_vow_bw_en",local_1c[0]);
      if (iVar1 == 0) goto LAB_00043f1c;
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_bw_en");
      }
    }
  }
  return 0;
}

