// module: mt7915.ko
// function: SetThermalProtectDisable @ 0xc279c
// size: 380 bytes
//

undefined4 SetThermalProtectDisable(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters !!\n","SetThermalProtectDisable");
    }
    return 0;
  }
  iVar4 = rstrtok(param_2,&_LC156);
  if (iVar4 == 0) {
    uVar3 = 0;
    uVar2 = 0;
    uVar1 = 0;
  }
  else {
    uVar1 = os_str_tol(iVar4,0,10);
    iVar4 = rstrtok(0,&_LC156);
    if (iVar4 == 0) {
      uVar3 = 0;
      uVar2 = 0;
    }
    else {
      uVar2 = os_str_tol(iVar4,0,10);
      iVar4 = rstrtok(0,&_LC156);
      if (iVar4 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = os_str_tol(iVar4,0,10);
        iVar4 = rstrtok(0,&_LC156);
        if (iVar4 != 0) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: wrong param format.\n","SetThermalProtectDisable");
          return 0;
        }
      }
    }
  }
  if (0 < DebugLevel) {
    printk("%s(): band_idx: %d, protection_type: %d, trigger_type: %d\n","SetThermalProtectDisable",
           uVar1,uVar2,uVar3);
  }
  MtCmdThermalProtectDisable(param_1,uVar1,uVar2,uVar3);
  return 1;
}

