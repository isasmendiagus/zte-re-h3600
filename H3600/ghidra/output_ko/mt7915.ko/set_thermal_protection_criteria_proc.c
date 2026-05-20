// module: mt7915.ko
// function: set_thermal_protection_criteria_proc @ 0xbcf8c
// size: 1008 bytes
//

undefined4 set_thermal_protection_criteria_proc(int *param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  char *pcVar10;
  char cVar11;
  int iVar12;
  uint uVar13;
  uint local_30;
  undefined4 local_2c;
  
  iVar7 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: No parameters!!\n","set_thermal_protection_criteria_proc");
  }
  else {
    iVar8 = rstrtok(param_2,&_LC156);
    if (iVar8 != 0) {
      cVar1 = '\0';
      cVar6 = '\0';
      cVar4 = '\0';
      cVar5 = '\0';
      cVar11 = '\0';
      local_2c = 0;
      local_30 = 0;
      uVar2 = 0;
      uVar3 = 0;
      do {
        switch(cVar11) {
        case '\0':
          uVar3 = simple_strtol(iVar8,0,10);
          break;
        case '\x01':
          uVar2 = simple_strtol(iVar8,0,10);
          break;
        case '\x02':
          local_30 = simple_strtol(iVar8,0,10);
          local_30 = local_30 & 0xff;
          break;
        case '\x03':
          cVar5 = simple_strtol(iVar8,0,10);
          break;
        case '\x04':
          cVar4 = simple_strtol(iVar8,0,10);
          break;
        case '\x05':
          cVar6 = simple_strtol(iVar8,0,10);
          break;
        case '\x06':
          local_2c = simple_strtol(iVar8,0,10);
          break;
        case '\a':
          cVar1 = simple_strtol(iVar8,0,10);
          break;
        default:
          if (-1 < DebugLevel) {
            printk("%s: Invalid Parameter Format!!\n","set_thermal_protection_criteria_proc");
          }
        }
        cVar11 = cVar11 + '\x01';
        iVar8 = rstrtok(0,&_LC156);
      } while (iVar8 != 0);
      if (cVar11 == '\b') {
        if (iVar7 != 0) {
          uVar9 = HcGetBandByWdev(iVar7);
          if (0 < DebugLevel) {
            iVar12 = (int)cVar5;
            iVar8 = (int)cVar4;
            iVar7 = (int)cVar6;
            uVar13 = local_30;
            printk("%s: fgHighEn: %d, fgLowEn: %d, fgRFOffEn: %d, cHighTempTh: %d, cLowTempTh: %d, cRFOffTh: %d\n"
                   ,"set_thermal_protection_criteria_proc",uVar3,uVar2,local_30,iVar12,iVar8,iVar7);
            if (0 < DebugLevel) {
              pcVar10 = "TxStream";
              if (cVar1 != '\0') {
                pcVar10 = "Duty Cycle";
              }
              printk("%s: u4RechkTimer: %d, ucType: %s\n","set_thermal_protection_criteria_proc",
                     local_2c,pcVar10,uVar13,iVar12,iVar8,iVar7);
            }
          }
          AsicThermalProtect(param_1,uVar9,uVar3,(int)cVar5,uVar2,(int)cVar4,local_2c,local_30,
                             (int)cVar6,cVar1);
          return 1;
        }
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s: wdev is invalid\n","set_thermal_protection_criteria_proc");
        return 0;
      }
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Wrong parameter format!!\n","set_thermal_protection_criteria_proc");
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk(&_LC253);
  if (DebugLevel < 1) {
LAB_000bd310:
    if (DebugLevel < 1) goto LAB_000bd380;
    printk("\tcLowTempTh:  (3-bit format) Low Temperature Protect Trigger point\n");
    if (DebugLevel < 1) {
      return 0;
    }
    printk("\tcRFOffTh:\t(3-bit format) RF off Protect Trigger point\n");
  }
  else {
    printk("\tfgHighEn:\t(1-bit format) High Temperature Protect Trigger Enable\n");
    if (DebugLevel < 1) {
      return 0;
    }
    printk("\tfgLowEn:\t (1-bit format) Low Temperature Protect Trigger Enable\n");
    if (0 < DebugLevel) {
      printk("\tfgRFOffEn:   (1-bit format) RF off Protect Trigger Enable\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\tcHighTempTh: (3-bit format) High Temperature Protect Trigger point\n");
      goto LAB_000bd310;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("\tu4RechkTimer:(4-bit format) Thermal Protect Recheck period\n");
  if (DebugLevel < 1) {
    return 0;
  }
  printk("\tucType:\t  (1-bit format) Thermal Protect Type (0: TxStream, 1: Duty Cycle)\n");
LAB_000bd380:
  if (0 < DebugLevel) {
    printk(&_LC262);
  }
  return 0;
}

