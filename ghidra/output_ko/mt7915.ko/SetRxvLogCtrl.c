// module: mt7915.ko
// function: SetRxvLogCtrl @ 0xc0b18
// size: 448 bytes
//

undefined4 SetRxvLogCtrl(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: no parameter.\n","SetRxvLogCtrl",param_3,DebugLevel,param_4);
      return 0;
    }
  }
  else {
    iVar3 = rstrtok(param_2,&_LC156);
    if (iVar3 == 0) {
      uVar2 = 0;
      uVar1 = 0;
      if (0 < DebugLevel) {
        printk("%s(): ctrl: %d, type_mask: %d\n","SetRxvLogCtrl",0,0,param_4);
        goto switchD_000c0bf4_caseD_0;
      }
    }
    else {
      uVar1 = os_str_tol(iVar3,0,10);
      iVar3 = rstrtok(0,&_LC156);
      uVar2 = 0;
      if (iVar3 != 0) {
        uVar2 = os_str_tol(iVar3,0,10);
        iVar3 = rstrtok(0,&_LC156);
        if (iVar3 != 0) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s(): number of parameters exceed expectation.\n","SetRxvLogCtrl");
          return 0;
        }
      }
      if (0 < DebugLevel) {
        printk("%s(): ctrl: %d, type_mask: %d\n","SetRxvLogCtrl",uVar1,uVar2,param_4);
        switch(uVar1) {
        case 0:
          goto switchD_000c0bf4_caseD_0;
        case 1:
          goto switchD_000c0bf4_caseD_1;
        case 2:
          goto switchD_000c0bf4_caseD_2;
        case 3:
          goto switchD_000c0bf4_caseD_3;
        case 4:
          goto switchD_000c0bf4_caseD_4;
        default:
          if (DebugLevel < 1) {
            return 0;
          }
          printk("%s(): invalid ctrl param(%d)\n","SetRxvLogCtrl",uVar1);
          return 0;
        }
      }
    }
    switch(uVar1) {
    case 0:
switchD_000c0bf4_caseD_0:
      chip_rxv_dump_start(param_1);
      return 1;
    case 1:
switchD_000c0bf4_caseD_1:
      chip_rxv_dump_stop(param_1);
      return 1;
    case 2:
switchD_000c0bf4_caseD_2:
      chip_rxv_dump_buf_alloc(param_1,uVar2);
      return 1;
    case 3:
switchD_000c0bf4_caseD_3:
      chip_rxv_dump_buf_clear(param_1);
      return 1;
    case 4:
switchD_000c0bf4_caseD_4:
      return 1;
    }
  }
  return 0;
}

