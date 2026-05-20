// module: mt7915.ko
// function: set_thermal_protection_admin_ctrl_duty_proc @ 0xbd3a0
// size: 716 bytes
//

undefined4 set_thermal_protection_admin_ctrl_duty_proc(int *param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c [2];
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = 0;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: No parameters!!\n","set_thermal_protection_admin_ctrl_duty_proc");
  }
  else {
    uVar2 = sscanf(param_2,"%u:%u:%u:%u",&local_28,&local_24,&local_20,local_1c);
    if ((uVar2 & 0xff) == 4) {
      if (iVar1 == 0) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s: wdev is invalid\n","set_thermal_protection_admin_ctrl_duty_proc");
        return 0;
      }
      uVar3 = HcGetBandByWdev(iVar1);
      if (DebugLevel < 1) {
        if (100 < local_28) {
          return 0;
        }
        if (local_28 < local_24) {
          return 0;
        }
      }
      else {
        printk("%s: ucBand:%d, u4Lv0Duty:%d, u4Lv1Duty:%d, u4Lv2Duty:%d, u4Lv3Duty:%d\n",
               "set_thermal_protection_admin_ctrl_duty_proc",uVar3,local_28,local_24,local_20,
               local_1c[0]);
        if (100 < local_28) {
          if (DebugLevel < 1) {
            return 0;
          }
          printk("Parameters error! Lv0Duty > 100\n");
          return 0;
        }
        if (local_28 < local_24) {
          if (DebugLevel < 1) {
            return 0;
          }
          printk("Parameters error! Lv1Duty > Lv0Duty");
          return 0;
        }
      }
      if (local_24 < local_20) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk("Parameters error! Lv2Duty > Lv1Duty");
        return 0;
      }
      if (local_1c[0] <= local_20) {
        AsicThermalProtectAdmitDuty(param_1,uVar3,local_28,local_24,local_20,local_1c[0]);
        return 1;
      }
      if (DebugLevel < 1) {
        return 0;
      }
      printk("Parameters error! Lv3Duty > Lv2Duty");
      return 0;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Wrong parameter format!!\n","set_thermal_protection_admin_ctrl_duty_proc");
  }
  if (0 < DebugLevel) {
    printk(&_LC269);
    if (0 < DebugLevel) {
      printk("\tLv0Duty: (3-bit format) Level 0 Protect Duty cycle\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\tLv1Duty: (3-bit format) Level 1 Protect Duty cycle\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\tLv2Duty: (3-bit format) Level 2 Protect Duty cycle\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\tLv3Duty: (3-bit format) Level 3 Protect Duty cycle\n");
    }
    if (0 < DebugLevel) {
      printk(&_LC274);
      return 0;
    }
  }
  return 0;
}

