// module: mt7915.ko
// function: SetThermoCompCtrl @ 0xbfa3c
// size: 572 bytes
//

undefined4 SetThermoCompCtrl(int *param_1,char *param_2)

{
  byte bVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  uint uVar6;
  
  cVar5 = *(char *)((int)param_1 + 0x286285);
  if (cVar5 == '\x01') {
    if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
      return 0;
    }
    uVar6 = HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
    cVar5 = *(char *)((int)param_1 + 0x286285);
  }
  else {
    uVar6 = 0;
  }
  if (cVar5 == '\0') {
    uVar6 = HcGetBandByWdev(param_1 + 0xdb6d6);
  }
  if (0 < DebugLevel) {
    printk("%s: ucBandIdx = %d\n","SetThermoCompCtrl",uVar6);
  }
  if (uVar6 < 2) {
    if (param_2 == (char *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: No parameters!!\n","SetThermoCompCtrl");
      }
    }
    else {
      sVar2 = strlen(param_2);
      if (sVar2 == 1) {
        iVar3 = rstrtok(param_2,&_LC156);
        if (iVar3 == 0) {
          bVar1 = 0;
        }
        else {
          bVar1 = 0;
          cVar5 = '\0';
          do {
            if (cVar5 == '\0') {
              bVar1 = simple_strtol(iVar3,0,10);
              iVar3 = rstrtok(0,&_LC156);
              cVar5 = '\x01';
              if (iVar3 == 0) break;
            }
            if (-1 < DebugLevel) {
              printk("%s: set wrong parameters\n","SetThermoCompCtrl");
            }
            cVar5 = cVar5 + '\x01';
            iVar3 = rstrtok(0,&_LC156);
          } while (iVar3 != 0);
          if (1 < bVar1) {
            if (DebugLevel < 0) {
              return 0;
            }
            printk("%s: Please input 1(Enable) or 0(Disable)!!\n","SetThermoCompCtrl");
            return 0;
          }
        }
        if (0 < DebugLevel) {
          printk("%s: fgThermoCompEn = %d\n","SetThermoCompCtrl",bVar1);
        }
        uVar4 = ThermoCompCtrl(param_1,bVar1,uVar6);
        return uVar4;
      }
      if ((-1 < DebugLevel) &&
         (printk("%s: Wrong parameter format!!\n","SetThermoCompCtrl"), -1 < DebugLevel)) {
        printk("%s: Please use input format like X (X = 0,1)!!\n","SetThermoCompCtrl");
      }
    }
  }
  return 0;
}

