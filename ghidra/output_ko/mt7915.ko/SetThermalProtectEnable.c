// module: mt7915.ko
// function: SetThermalProtectEnable @ 0xc2594
// size: 348 bytes
//

undefined4 SetThermalProtectEnable(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  int iVar5;
  char cVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters !!\n","SetThermalProtectEnable");
    }
    return 0;
  }
  iVar5 = rstrtok(param_2,&_LC156);
  if (iVar5 == 0) {
    uVar4 = 0;
    uVar1 = 0;
    uVar2 = 0;
    uVar3 = 0;
    uVar7 = 0;
    uVar8 = 0;
  }
  else {
    cVar6 = '\0';
    uVar4 = 0;
    uVar7 = 0;
    uVar8 = 0;
    uVar1 = 0;
    uVar2 = 0;
    uVar3 = 0;
    do {
      switch(cVar6) {
      case '\0':
        uVar3 = os_str_tol(iVar5,0,10);
        break;
      case '\x01':
        uVar2 = os_str_tol(iVar5,0,10);
        break;
      case '\x02':
        uVar1 = os_str_tol(iVar5,0,10);
        break;
      case '\x03':
        uVar8 = os_str_tol(iVar5,0,10);
        break;
      case '\x04':
        uVar7 = os_str_tol(iVar5,0,10);
        break;
      case '\x05':
        uVar4 = os_str_tol(iVar5,0,10);
        break;
      default:
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: wrong param format.\n","SetThermalProtectEnable");
        return 0;
      }
      cVar6 = cVar6 + '\x01';
      iVar5 = rstrtok(0,&_LC156);
    } while (iVar5 != 0);
  }
  if ((0 < DebugLevel) &&
     (printk("%s(): band_idx: %d, protection_type: %d, trigger_type: %d\n","SetThermalProtectEnable"
             ,uVar3,uVar2,uVar1), 0 < DebugLevel)) {
    printk("%s(): trigger_temp: %d, restore_temp: %d, recheck_time: %d\n","SetThermalProtectEnable",
           uVar8,uVar7,uVar4);
  }
  MtCmdThermalProtectEnable(param_1,uVar3,uVar2,uVar1,uVar8,uVar7,uVar4);
  return 1;
}

