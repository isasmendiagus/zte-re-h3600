// module: mt7915.ko
// function: SetSrNRTCtrlAll @ 0x170a2c
// size: 452 bytes
//

int SetSrNRTCtrlAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  undefined2 uVar5;
  uint uVar6;
  undefined2 uVar7;
  uint uVar8;
  undefined2 uVar9;
  uint uVar10;
  uint uVar11;
  undefined1 uVar12;
  uint uVar13;
  uint local_44;
  undefined1 local_40;
  char local_3f;
  undefined1 local_3e;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev();
  os_zero_mem(&local_40,0x18);
  local_40 = 0xe;
  local_3f = '\x06';
  local_3e = uVar1;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrNRTCtrlAll");
  }
  else {
    iVar2 = rstrtok(param_2,&_LC44);
    if (iVar2 != 0) {
      uVar6 = 0;
      cVar4 = '\x01';
      uVar8 = 0;
      uVar10 = 0;
      uVar13 = 0;
      uVar11 = 0;
      local_44 = 0;
      do {
        uVar12 = (undefined1)uVar13;
        uVar1 = (undefined1)uVar11;
        switch(cVar4) {
        case '\x01':
          local_44 = simple_strtol(iVar2,0,10);
          if (1 < local_44) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",0,local_44);
            }
            goto LAB_00170bdc;
          }
          break;
        case '\x02':
          uVar11 = simple_strtol(iVar2,0,10);
          if (1 < uVar11) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",1,uVar11);
            }
            goto LAB_00170bdc;
          }
          break;
        case '\x03':
          uVar13 = simple_strtol(iVar2,0,10);
          if (1 < uVar13) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",2,uVar13);
            }
            goto LAB_00170bdc;
          }
          break;
        case '\x04':
          uVar10 = simple_strtol(iVar2,0,10);
          if (uVar10 < 0x10001) break;
          iVar3 = FUN_0016b374(uVar10,3,0,0x10000);
LAB_00170b7c:
          uVar5 = (undefined2)uVar6;
          uVar7 = (undefined2)uVar8;
          uVar9 = (undefined2)uVar10;
          iVar2 = rstrtok(0,&_LC44);
          if (iVar2 != 0) {
            if (iVar3 != 1) goto LAB_00170b14;
            goto LAB_00170bf0;
          }
          if (iVar3 == 1) goto LAB_00170bf0;
          goto LAB_00170ce0;
        case '\x05':
          uVar8 = simple_strtol(iVar2,0,10);
          if (0x10000 < uVar8) {
            iVar3 = FUN_0016b374(uVar8,4,0,0x10000);
            goto LAB_00170b7c;
          }
          break;
        case '\x06':
          uVar6 = simple_strtol(iVar2,0,10);
          if (0x10000 < uVar6) {
            iVar3 = FUN_0016b374(uVar6,5,0,0x10000);
            goto LAB_00170b7c;
          }
          break;
        default:
          goto LAB_00170c9c;
        }
        uVar5 = (undefined2)uVar6;
        uVar7 = (undefined2)uVar8;
        uVar9 = (undefined2)uVar10;
        uVar12 = (undefined1)uVar13;
        uVar1 = (undefined1)uVar11;
        iVar2 = rstrtok(0,&_LC44);
        if (iVar2 == 0) goto LAB_00170ce0;
LAB_00170b14:
        cVar4 = cVar4 + '\x01';
      } while( true );
    }
    cVar4 = '\0';
    uVar5 = 0;
    uVar7 = 0;
    uVar9 = 0;
    uVar1 = 0;
    uVar12 = 0;
    local_44._0_1_ = 0;
LAB_00170ce0:
    if (local_3f == cVar4) {
      local_34 = (undefined1)local_44;
      local_33 = uVar1;
      local_32 = uVar12;
      local_30 = uVar9;
      local_2e = uVar7;
      local_2c = uVar5;
      iVar2 = SrCmdSRUpdateNRTCtrl(param_1,&local_40);
      if (iVar2 != 1) {
        return iVar2;
      }
    }
    else {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Format Error! ArgNum = %d != %d\n","SetSrNRTCtrlAll",cVar4);
    }
  }
LAB_00170bf0:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set srnrtctrl=[SrtEn]-[SrtSrpEn]-[SrtAddrOrderEn]-[SrtInRcpiTh]-[SrtOutRcpiTh]-[SrtUsedCntTh]\n"
           ,"SetSrNRTCtrlAll");
  }
  return 1;
LAB_00170c9c:
  if (-1 < DebugLevel) {
    printk("%s: set wrong parameters\n","SetSrNRTCtrlAll");
  }
LAB_00170bdc:
  rstrtok(0,&_LC44);
  goto LAB_00170bf0;
}

