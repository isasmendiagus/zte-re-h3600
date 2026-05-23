// module: mt7915.ko
// function: set_pp_cap_ctrl @ 0x171b78
// size: 344 bytes
//

int set_pp_cap_ctrl(int *param_1,char *param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 local_1c;
  int local_18;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  local_1c = 0;
  local_18 = 0;
  if (iVar2 != 0) {
    uVar1 = HcGetBandByWdev();
    os_zero_mem(&local_14,4);
    local_14 = 1;
    local_13 = uVar1;
    if (param_2 == (char *)0x0) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Arg is Null\n","set_pp_cap_ctrl");
    }
    else {
      iVar2 = sscanf(param_2,"%u-%u",&local_18,&local_1c);
      if (iVar2 != 2) {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("Format Error! Please enter in the following format\nPpAuto-PpEn\n");
        return 1;
      }
      if (2 < DebugLevel) {
        printk("%s: pp_auto %d, pp_ctrl %d\n","set_pp_cap_ctrl",local_18,local_1c);
      }
      local_11 = local_18 != 0;
      local_12 = (undefined1)local_1c;
      iVar2 = pp_cmd_cap_ctrl(param_1,&local_14);
      if (iVar2 != 1) {
        return iVar2;
      }
    }
    if (-1 < DebugLevel) {
      printk("%s: iwpriv rax0 set ppcapctrl=[PpAuto]-[PpEn]\n","set_pp_cap_ctrl");
    }
  }
  return 1;
}

