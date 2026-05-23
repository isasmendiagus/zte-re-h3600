// module: mt7915.ko
// function: SetATEForceTxPower @ 0x261820
// size: 816 bytes
//

bool SetATEForceTxPower(int param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  char cVar5;
  int iVar6;
  size_t sVar7;
  int iVar8;
  
  iVar8 = *(int *)(param_1 + 0xa39fd4);
  iVar6 = net_ad_wrap_service();
  uVar1 = *(undefined1 *)(iVar6 + 0x4cc);
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return false;
    }
    printk("%s: No Parameters !! \n","SetATEForceTxPower");
  }
  else {
    sVar7 = strlen(param_2);
    if (sVar7 == 0xb) {
      iVar6 = rstrtok(param_2,&_LC2);
      if (iVar6 == 0) {
        uVar4 = 0;
        cVar5 = '\0';
        uVar3 = 0;
        uVar2 = 0;
LAB_00261ab4:
        if (0 < DebugLevel) {
          printk("%s: Band(%d), TxMode(%d), MCS(%d), BW(%d), TxPower(%d)\n","SetATEForceTxPower",
                 uVar1,uVar2,uVar3,uVar4,(int)cVar5);
        }
        iVar6 = (**(code **)(iVar8 + 0x3c))(param_1,(int)cVar5,uVar2,uVar3,uVar4);
        return iVar6 == 0;
      }
      uVar2 = simple_strtol(iVar6,0,10);
      iVar6 = rstrtok(0,&_LC2);
      if (iVar6 == 0) {
        uVar4 = 0;
        cVar5 = '\0';
        uVar3 = 0;
        goto LAB_00261ab4;
      }
      uVar3 = simple_strtol(iVar6,0,10);
      iVar6 = rstrtok(0,&_LC2);
      if (iVar6 == 0) {
        uVar4 = 0;
        cVar5 = '\0';
        goto LAB_00261ab4;
      }
      uVar4 = simple_strtol(iVar6,0,10);
      iVar6 = rstrtok(0,&_LC2);
      cVar5 = '\0';
      if (iVar6 == 0) goto LAB_00261ab4;
      cVar5 = simple_strtol(iVar6,0,10);
      iVar6 = rstrtok(0,&_LC2);
      if (iVar6 == 0) goto LAB_00261ab4;
      if (DebugLevel < 0) {
        return false;
      }
      printk("%s: Set Too Much Parameters !!\n","SetATEForceTxPower");
    }
    else {
      if (DebugLevel < 0) {
        return false;
      }
      printk("%s: Wrong Parameter Format !!\n","SetATEForceTxPower");
    }
  }
  if (DebugLevel < 0) {
LAB_00261908:
    if (-1 < DebugLevel) {
      printk(&_LC32);
      if (DebugLevel < 0) {
        return false;
      }
      printk(&_LC33);
      goto LAB_00261940;
    }
  }
  else {
    printk(&_LC28);
    if (DebugLevel < 0) {
      return false;
    }
    printk(&_LC29);
    if (-1 < DebugLevel) {
      printk(&_LC30);
      if (DebugLevel < 0) {
        return false;
      }
      printk(&_LC31);
      goto LAB_00261908;
    }
LAB_00261940:
    if (DebugLevel < 0) goto LAB_002619b0;
    printk(&_LC34);
    if (DebugLevel < 0) {
      return false;
    }
    printk(&_LC35);
  }
  if (DebugLevel < 0) {
    return false;
  }
  printk(&_LC36);
  if (DebugLevel < 0) {
    return false;
  }
  printk(&_LC37);
LAB_002619b0:
  if (-1 < DebugLevel) {
    printk(&_LC38);
  }
  return false;
}

