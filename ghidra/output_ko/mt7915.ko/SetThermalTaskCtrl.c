// module: mt7915.ko
// function: SetThermalTaskCtrl @ 0xc23a8
// size: 488 bytes
//

undefined4 SetThermalTaskCtrl(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  size_t sVar4;
  int iVar5;
  undefined4 uVar6;
  char cVar7;
  
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters !!\n","SetThermalTaskCtrl");
    }
  }
  else {
    sVar4 = strlen(param_2);
    if (sVar4 == 7) {
      iVar5 = rstrtok(param_2,&_LC156);
      if (iVar5 == 0) {
        uVar2 = 0;
        uVar1 = 0;
        uVar3 = 0;
      }
      else {
        uVar2 = 0;
        uVar1 = 0;
        uVar3 = 0;
        cVar7 = '\0';
        do {
          if (cVar7 == '\x01') {
LAB_000c24b4:
            uVar2 = os_str_tol(iVar5,0,10);
            iVar5 = rstrtok(0,&_LC156);
            if (iVar5 == 0) break;
LAB_000c2454:
            uVar1 = os_str_tol(iVar5,0,10);
            iVar5 = rstrtok(0,&_LC156);
            if (iVar5 == 0) break;
            cVar7 = '\x03';
          }
          else {
            if (cVar7 == '\0') {
              uVar3 = os_str_tol(iVar5,0,10);
              iVar5 = rstrtok(0,&_LC156);
              if (iVar5 != 0) goto LAB_000c24b4;
              break;
            }
            if (cVar7 == '\x02') goto LAB_000c2454;
          }
          if (-1 < DebugLevel) {
            printk("%s: Wrong parameters !!\n","SetThermalTaskCtrl");
          }
          cVar7 = cVar7 + '\x01';
          iVar5 = rstrtok(0,&_LC156);
        } while (iVar5 != 0);
      }
      if (0 < DebugLevel) {
        printk("%s(): u1BandIdx: %d, fgTrigEn: %d, u1Thres: %d\n","SetThermalTaskCtrl",uVar3,uVar1,
               uVar2);
      }
      uVar6 = ThermalTaskCtrl(param_1,uVar3,uVar1,uVar2);
      return uVar6;
    }
    if (-1 < DebugLevel) {
      printk("%s: Wrong parameter format !!\n","SetThermalTaskCtrl");
    }
  }
  return 0;
}

