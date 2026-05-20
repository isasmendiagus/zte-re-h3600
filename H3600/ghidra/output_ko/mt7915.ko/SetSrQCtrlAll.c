// module: mt7915.ko
// function: SetSrQCtrlAll @ 0x16fe90
// size: 736 bytes
//

int SetSrQCtrlAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  char cVar7;
  undefined1 local_2c;
  char local_2b;
  undefined1 local_2a;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined4 local_1c;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev();
  os_zero_mem(&local_2c,0x14);
  local_2b = '\x04';
  local_2c = 10;
  local_2a = uVar1;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrQCtrlAll");
    goto LAB_0016ff40;
  }
  iVar2 = rstrtok(param_2,&_LC44);
  if (iVar2 == 0) {
    cVar7 = '\0';
    uVar6 = 0;
    uVar5 = 0;
    uVar4 = 0;
    uVar3 = 0;
  }
  else {
    uVar3 = simple_strtol(iVar2,0,10);
    if (1 < uVar3) {
      if (-1 < DebugLevel) {
        printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",0,uVar3);
      }
LAB_0016ff2c:
      rstrtok(0,&_LC44);
      goto LAB_0016ff40;
    }
    iVar2 = rstrtok(0,&_LC44);
    if (iVar2 == 0) {
      cVar7 = '\x01';
      uVar6 = 0;
      uVar5 = 0;
      uVar4 = 0;
    }
    else {
      uVar4 = simple_strtol(iVar2,0,10);
      if (1 < uVar4) {
        if (-1 < DebugLevel) {
          printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",1,uVar4);
        }
        goto LAB_0016ff2c;
      }
      iVar2 = rstrtok(0,&_LC44);
      if (iVar2 == 0) {
        cVar7 = '\x02';
        uVar6 = 0;
        uVar5 = 0;
      }
      else {
        uVar5 = simple_strtol(iVar2,0,10);
        if (1 < uVar5) {
          if (-1 < DebugLevel) {
            printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",2,uVar5);
          }
          goto LAB_0016ff2c;
        }
        iVar2 = rstrtok(0,&_LC44);
        if (iVar2 == 0) {
          cVar7 = '\x03';
          uVar6 = 0;
        }
        else {
          uVar6 = simple_strtol(iVar2,0,10);
          iVar2 = rstrtok(0,&_LC44);
          if (iVar2 != 0) {
            if (-1 < DebugLevel) {
              printk("%s: set wrong parameters\n","SetSrQCtrlAll");
            }
            goto LAB_0016ff2c;
          }
          cVar7 = '\x04';
        }
      }
    }
  }
  if (local_2b == cVar7) {
    local_20 = (undefined1)uVar3;
    local_1f = (undefined1)uVar4;
    local_1e = (undefined1)uVar5;
    local_1c = uVar6;
    iVar2 = SrCmdSRUpdateQCtrl(param_1,&local_2c);
    if (iVar2 != 1) {
      return iVar2;
    }
  }
  else {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Format Error! ArgNum = %d != %d\n","SetSrQCtrlAll");
  }
LAB_0016ff40:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set srqctrl=[SrRxRptEn]-[SrCw]-[SrSuspend]-[SrBackOffMask]\n",
           "SetSrQCtrlAll");
  }
  return 1;
}

