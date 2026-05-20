// module: mt7915.ko
// function: SetThermalProtectDutyInfo @ 0xc2ba4
// size: 260 bytes
//

undefined4 SetThermalProtectDutyInfo(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 auStack_15 [9];
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters !!\n","SetThermalProtectDutyInfo");
    }
    return 0;
  }
  iVar2 = rstrtok(param_2,&_LC156);
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = os_str_tol(iVar2,0,10);
    iVar2 = rstrtok(0,&_LC156);
    if (iVar2 != 0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: wrong param format.\n","SetThermalProtectDutyInfo");
      return 0;
    }
  }
  if (0 < DebugLevel) {
    printk("%s(): band_idx: %d\n","SetThermalProtectDutyInfo",uVar1);
  }
  MtCmdThermalProtectDutyInfo(param_1,uVar1,auStack_15);
  return 1;
}

