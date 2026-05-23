// module: mt7915.ko
// function: SetThermalProtectStateAct @ 0xc2cac
// size: 460 bytes
//

undefined4 SetThermalProtectStateAct(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters !!\n","SetThermalProtectStateAct");
    }
    return 0;
  }
  iVar5 = rstrtok(param_2,&_LC156);
  if (iVar5 == 0) {
    uVar4 = 0;
    uVar3 = 0;
    uVar1 = 0;
    uVar2 = 0;
  }
  else {
    uVar1 = os_str_tol(iVar5,0,10);
    iVar5 = rstrtok(0,&_LC156);
    if (iVar5 == 0) {
      uVar4 = 0;
      uVar3 = 0;
      uVar2 = 0;
    }
    else {
      uVar2 = os_str_tol(iVar5,0,10);
      iVar5 = rstrtok(0,&_LC156);
      if (iVar5 == 0) {
        uVar4 = 0;
        uVar3 = 0;
      }
      else {
        uVar3 = os_str_tol(iVar5,0,10);
        iVar5 = rstrtok(0,&_LC156);
        uVar4 = 0;
        if (iVar5 != 0) {
          uVar4 = os_str_tol(iVar5,0,10);
          iVar5 = rstrtok(0,&_LC156);
          if (iVar5 != 0) {
            if (DebugLevel < 0) {
              return 0;
            }
            printk("%s: wrong param format.\n","SetThermalProtectStateAct");
            return 0;
          }
        }
      }
    }
  }
  if ((0 < DebugLevel) &&
     (printk("%s(): band_idx: %d, protect_type: %d\n","SetThermalProtectStateAct",uVar1,uVar2),
     0 < DebugLevel)) {
    printk("%s(): trig_type: %d, state: %d\n","SetThermalProtectStateAct",uVar3,uVar4);
  }
  MtCmdThermalProtectStateAct(param_1,uVar1,uVar2,uVar3,uVar4);
  return 1;
}

