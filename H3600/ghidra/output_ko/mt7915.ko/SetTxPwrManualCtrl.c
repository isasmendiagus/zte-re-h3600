// module: mt7915.ko
// function: SetTxPwrManualCtrl @ 0xc1284
// size: 884 bytes
//

bool SetTxPwrManualCtrl(int *param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  undefined4 uVar5;
  size_t sVar6;
  int iVar7;
  
  if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
    return false;
  }
  HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
  uVar5 = HcGetBandByWdev(param_1 + 0xdb6d6);
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return false;
    }
    printk("%s: No Parameters !! \n","SetTxPwrManualCtrl");
  }
  else {
    sVar6 = strlen(param_2);
    if (sVar6 == 0xb) {
      iVar7 = rstrtok(param_2,&_LC156);
      if (iVar7 == 0) {
        uVar3 = 0;
        cVar4 = '\0';
        uVar2 = 0;
        uVar1 = 0;
LAB_000c1558:
        if (0 < DebugLevel) {
          printk("%s: Band(%d), TxMode(%d), MCS(%d), BW(%d), TxPower(%d)\n","SetTxPwrManualCtrl",
                 uVar5,uVar1,uVar2,uVar3,(int)cVar4);
        }
        iVar7 = TxPowerManualCtrl(param_1,uVar5,(int)cVar4,uVar1,uVar2,uVar3);
        return iVar7 == 0;
      }
      uVar1 = simple_strtol(iVar7,0,10);
      iVar7 = rstrtok(0,&_LC156);
      if (iVar7 == 0) {
        uVar3 = 0;
        cVar4 = '\0';
        uVar2 = 0;
        goto LAB_000c1558;
      }
      uVar2 = simple_strtol(iVar7,0,10);
      iVar7 = rstrtok(0,&_LC156);
      if (iVar7 == 0) {
        uVar3 = 0;
        cVar4 = '\0';
        goto LAB_000c1558;
      }
      uVar3 = simple_strtol(iVar7,0,10);
      iVar7 = rstrtok(0,&_LC156);
      if (iVar7 == 0) {
        cVar4 = '\0';
        goto LAB_000c1558;
      }
      cVar4 = simple_strtol(iVar7,0,10);
      iVar7 = rstrtok(0,&_LC156);
      if (iVar7 == 0) goto LAB_000c1558;
      if (DebugLevel < 0) {
        return false;
      }
      printk("%s: Set Too Much Parameters !!\n","SetTxPwrManualCtrl");
    }
    else {
      if (DebugLevel < 0) {
        return false;
      }
      printk("%s: Wrong Parameter Format !!\n","SetTxPwrManualCtrl");
    }
  }
  if (DebugLevel < 0) {
LAB_000c148c:
    if (-1 < DebugLevel) {
      printk(&_LC382);
      if (DebugLevel < 0) {
        return false;
      }
      printk(&_LC383);
      goto LAB_000c14c4;
    }
  }
  else {
    printk(&_LC378);
    if (DebugLevel < 0) {
      return false;
    }
    printk(&_LC379);
    if (-1 < DebugLevel) {
      printk(&_LC380);
      if (DebugLevel < 0) {
        return false;
      }
      printk(&_LC381);
      goto LAB_000c148c;
    }
LAB_000c14c4:
    if (DebugLevel < 0) goto LAB_000c1534;
    printk(&_LC384);
    if (DebugLevel < 0) {
      return false;
    }
    printk(&_LC385);
  }
  if (DebugLevel < 0) {
    return false;
  }
  printk(&_LC386);
  if (DebugLevel < 0) {
    return false;
  }
  printk(&_LC387);
LAB_000c1534:
  if (-1 < DebugLevel) {
    printk(&_LC388);
  }
  return false;
}

