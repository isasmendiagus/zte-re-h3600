// module: mt7915.ko
// function: set_re_calibration @ 0xbb544
// size: 908 bytes
//

undefined4 set_re_calibration(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  char *local_1c [2];
  
  local_1c[0] = param_2;
  if (0 < DebugLevel) {
    printk(":%s: arg = %s\n","set_re_calibration",param_2);
  }
  pcVar1 = strsep(local_1c,":");
  if ((pcVar1 == (char *)0x0) || (local_1c[0] == (char *)0x0)) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk(":%s: Invalid parameters\n","set_re_calibration");
    return 0;
  }
  uVar2 = os_str_toul(pcVar1,0,10);
  uVar3 = os_str_toul(local_1c[0],0,10);
  if (1 < uVar2) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk(":%s: Unknown BandIdx = %d\n","set_re_calibration",uVar2);
    return 0;
  }
  if (uVar3 - 3 < 2 || 0xc < uVar3) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk(":%s: Unknown CalItem = %d\n","set_re_calibration",uVar3);
    return 0;
  }
  if (0 < DebugLevel) {
    printk(":%s: BandIdx: %d, CalItem: %d\n","set_re_calibration",uVar2,uVar3);
    switch(uVar3) {
    case 0:
      if (0 < DebugLevel) {
        printk(":%s: RC_CAL\n","set_re_calibration");
        uVar4 = 1;
        break;
      }
switchD_000bb628_caseD_0:
      uVar4 = 1;
      break;
    case 1:
      if (0 < DebugLevel) {
        printk(":%s: RX_RSSI_DCOC_CAL\n","set_re_calibration");
        uVar4 = 2;
        break;
      }
switchD_000bb628_caseD_1:
      uVar4 = 2;
      break;
    case 2:
      if (0 < DebugLevel) {
        printk(":%s: RX_DCOC_CAL\n","set_re_calibration");
        uVar4 = 4;
        break;
      }
switchD_000bb628_caseD_2:
      uVar4 = 4;
      break;
    default:
      if (0 < DebugLevel) {
        printk(":%s: Unknown CalItem = %d\n","set_re_calibration",uVar3);
        uVar4 = 0;
        break;
      }
switchD_000bb628_caseD_3:
      uVar4 = 0;
      break;
    case 5:
      if (0 < DebugLevel) {
        printk(":%s: RX_FIIQ_CAL\n","set_re_calibration");
        uVar4 = 0x20;
        break;
      }
switchD_000bb628_caseD_5:
      uVar4 = 0x20;
      break;
    case 6:
      if (0 < DebugLevel) {
        printk(":%s: RX_FDIQ_CAL\n","set_re_calibration");
        uVar4 = 0x40;
        break;
      }
switchD_000bb628_caseD_6:
      uVar4 = 0x40;
      break;
    case 7:
      if (0 < DebugLevel) {
        printk(":%s: TX_DPD_LINK\n","set_re_calibration");
        uVar4 = 0x80;
        break;
      }
switchD_000bb628_caseD_7:
      uVar4 = 0x80;
      break;
    case 8:
      if (0 < DebugLevel) {
        printk(":%s: TX_LPFG\n","set_re_calibration");
        uVar4 = 0x100;
        break;
      }
switchD_000bb628_caseD_8:
      uVar4 = 0x100;
      break;
    case 9:
      if (0 < DebugLevel) {
        printk(":%s: TX_DCIQC\n","set_re_calibration");
        uVar4 = 0x200;
        break;
      }
switchD_000bb628_caseD_9:
      uVar4 = 0x200;
      break;
    case 10:
      if (0 < DebugLevel) {
        printk(":%s: TX_IQM\n","set_re_calibration");
        uVar4 = 0x400;
        break;
      }
switchD_000bb628_caseD_a:
      uVar4 = 0x400;
      break;
    case 0xb:
      if (0 < DebugLevel) {
        printk(":%s: TX_PGA\n","set_re_calibration");
        uVar4 = 0x800;
        break;
      }
switchD_000bb628_caseD_b:
      uVar4 = 0x800;
      break;
    case 0xc:
      if (0 < DebugLevel) {
        printk(":%s: CAL_ALL\n","set_re_calibration");
        uVar4 = 0x80000000;
        break;
      }
switchD_000bb628_caseD_c:
      uVar4 = 0x80000000;
    }
    MtCmdDoCalibration(param_1,1,uVar4,uVar2);
    return 1;
  }
  switch(uVar3) {
  case 0:
    goto switchD_000bb628_caseD_0;
  case 1:
    goto switchD_000bb628_caseD_1;
  case 2:
    goto switchD_000bb628_caseD_2;
  default:
    goto switchD_000bb628_caseD_3;
  case 5:
    goto switchD_000bb628_caseD_5;
  case 6:
    goto switchD_000bb628_caseD_6;
  case 7:
    goto switchD_000bb628_caseD_7;
  case 8:
    goto switchD_000bb628_caseD_8;
  case 9:
    goto switchD_000bb628_caseD_9;
  case 10:
    goto switchD_000bb628_caseD_a;
  case 0xb:
    goto switchD_000bb628_caseD_b;
  case 0xc:
    goto switchD_000bb628_caseD_c;
  }
}

