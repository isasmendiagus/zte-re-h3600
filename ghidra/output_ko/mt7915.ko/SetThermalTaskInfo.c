// module: mt7915.ko
// function: SetThermalTaskInfo @ 0xc2248
// size: 348 bytes
//

undefined4 SetThermalTaskInfo(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters !!\n","SetThermalTaskInfo");
    }
  }
  else {
    sVar2 = strlen(param_2);
    if (sVar2 == 1) {
      iVar3 = rstrtok(param_2,&_LC156);
      if (iVar3 == 0) {
        uVar1 = 0;
      }
      else {
        cVar5 = '\0';
        uVar1 = 0;
        do {
          if (cVar5 == '\0') {
            uVar1 = os_str_tol(iVar3,0,10);
            iVar3 = rstrtok(0,&_LC156);
            cVar5 = '\x01';
            if (iVar3 == 0) break;
          }
          if (-1 < DebugLevel) {
            printk("%s: Wrong parameters !!\n","SetThermalTaskInfo");
          }
          cVar5 = cVar5 + '\x01';
          iVar3 = rstrtok(0,&_LC156);
        } while (iVar3 != 0);
      }
      if (0 < DebugLevel) {
        printk("%s(): u1BandIdx: %d\n","SetThermalTaskInfo",uVar1);
      }
      uVar4 = ThermalBasicInfo(param_1,uVar1);
      return uVar4;
    }
    if (-1 < DebugLevel) {
      printk("%s: Wrong parameter format !!\n","SetThermalTaskInfo");
    }
  }
  return 0;
}

