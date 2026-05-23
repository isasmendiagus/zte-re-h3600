// module: mt7915.ko
// function: SetSrSrgBitmap @ 0x170ecc
// size: 588 bytes
//

int SetSrSrgBitmap(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char cVar7;
  undefined1 local_4c;
  char local_4b;
  undefined1 local_4a;
  undefined4 auStack_40 [8];
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    return 1;
  }
  iVar1 = HcGetBandByWdev();
  cVar7 = '\x04';
  os_zero_mem(&local_4c,0x2c);
  local_4a = (undefined1)iVar1;
  local_4c = 0x1d;
  local_4b = '\x04';
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrSrgBitmap");
  }
  else {
    iVar2 = rstrtok(param_2,&_LC44);
    if (iVar2 == 0) {
      cVar7 = '\0';
      uVar6 = 0;
      uVar5 = 0;
      uVar4 = 0;
      uVar3 = 0;
    }
    else {
      uVar3 = simple_strtol(iVar2,0,0x10);
      iVar2 = rstrtok(0,&_LC44);
      if (iVar2 == 0) {
        cVar7 = '\x01';
        uVar6 = 0;
        uVar5 = 0;
        uVar4 = 0;
      }
      else {
        uVar4 = simple_strtol(iVar2,0,0x10);
        iVar2 = rstrtok(0,&_LC44);
        if (iVar2 == 0) {
          cVar7 = '\x02';
          uVar6 = 0;
          uVar5 = 0;
        }
        else {
          uVar5 = simple_strtol(iVar2,0,0x10);
          iVar2 = rstrtok(0,&_LC44);
          if (iVar2 == 0) {
            cVar7 = '\x03';
            uVar6 = 0;
          }
          else {
            uVar6 = simple_strtol(iVar2,0,0x10);
            iVar2 = rstrtok(0,&_LC44);
            if (iVar2 != 0) {
              if (-1 < DebugLevel) {
                printk("%s: set wrong parameters\n","SetSrSrgBitmap");
              }
              rstrtok(0,&_LC44);
              goto LAB_00171004;
            }
          }
        }
      }
    }
    if (local_4b == cVar7) {
      auStack_40[iVar1] = uVar3;
      auStack_40[iVar1 + 2] = uVar4;
      auStack_40[iVar1 + 4] = uVar5;
      auStack_40[iVar1 + 6] = uVar6;
      iVar1 = SrCmdSRUpdateSrgBitmap(param_1,&local_4c);
      if (iVar1 != 1) {
        return iVar1;
      }
    }
    else {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Format Error! ArgNum = %d != %d\n","SetSrSrgBitmap");
    }
  }
LAB_00171004:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set srsrgbm=[Color_31_0]-[Color_63_32]-[pBssid_31_0]-[pBssid_63_32]\n",
           "SetSrSrgBitmap");
  }
  return 1;
}

