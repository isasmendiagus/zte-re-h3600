// module: mt7915.ko
// function: set_vow_group_dwrr_max_wait_time @ 0x43bc8
// size: 252 bytes
//

undefined4 set_vow_group_dwrr_max_wait_time(int param_1,char *param_2)

{
  int iVar1;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",local_14);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0xa7a2f3) = (char)local_14[0];
    if ((*(uint *)(param_1 + 0xa797a8) & 2) == 0) {
      if (-1 < DebugLevel) {
        printk("%s: set %u.\n","set_vow_group_dwrr_max_wait_time");
      }
    }
    else {
      iVar1 = FUN_000403f8(param_1);
      if (DebugLevel < 0) {
        if (iVar1 != 0) {
          return 0;
        }
      }
      else {
        printk("%s: set %u.\n","set_vow_group_dwrr_max_wait_time",local_14[0]);
        if (iVar1 != 0) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: set command failed.\n","set_vow_group_dwrr_max_wait_time");
          return 0;
        }
      }
    }
    return 1;
  }
  return 0;
}

