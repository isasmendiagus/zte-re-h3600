// module: mt7915.ko
// function: set_vow_bn_mon_period @ 0x47a74
// size: 204 bytes
//

undefined4 set_vow_bn_mon_period(int param_1,char *param_2)

{
  int iVar1;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",local_14);
  if (iVar1 != 0) {
    *(short *)(param_1 + 0xa7a302) = (short)local_14[0];
    iVar1 = vow_set_bad_node(param_1,2);
    if (DebugLevel < 0) {
      if (iVar1 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: period %u.\n","set_vow_bn_mon_period",local_14[0]);
      if (iVar1 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_bn_mon_period");
      }
    }
  }
  return 0;
}

