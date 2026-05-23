// module: mt7915.ko
// function: SetSrIBPDAll @ 0x17028c
// size: 440 bytes
//

int SetSrIBPDAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  undefined1 uVar6;
  uint uVar7;
  undefined1 uVar8;
  uint uVar9;
  undefined1 uVar10;
  uint uVar11;
  undefined1 uVar12;
  uint uVar13;
  undefined1 local_3c;
  char local_3b;
  undefined1 local_3a;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev();
  os_zero_mem(&local_3c,0x14);
  local_3c = 0xb;
  local_3b = '\x05';
  local_3a = uVar1;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrIBPDAll");
  }
  else {
    iVar2 = rstrtok(param_2,&_LC44);
    if (iVar2 != 0) {
      uVar5 = 0;
      cVar4 = '\x01';
      uVar13 = 0;
      uVar11 = 0;
      uVar9 = 0;
      uVar7 = 0;
      do {
        switch(cVar4) {
        case '\x01':
          uVar7 = simple_strtol(iVar2,0,10);
          if (uVar7 < 0x101) break;
          iVar3 = FUN_0016b374(uVar7,0,0,0x100);
LAB_00170434:
          uVar1 = (undefined1)uVar5;
          uVar12 = (undefined1)uVar13;
          uVar10 = (undefined1)uVar11;
          uVar8 = (undefined1)uVar9;
          uVar6 = (undefined1)uVar7;
          iVar2 = rstrtok(0,&_LC44);
          if (iVar2 != 0) {
            if (iVar3 != 1) goto LAB_0017036c;
            goto LAB_0017048c;
          }
          if (iVar3 == 1) goto LAB_0017048c;
          goto LAB_001704b8;
        case '\x02':
          uVar9 = simple_strtol(iVar2,0,10);
          if (0x100 < uVar9) {
            iVar3 = FUN_0016b374(uVar9,1,0,0x100);
            goto LAB_00170434;
          }
          break;
        case '\x03':
          uVar11 = simple_strtol(iVar2,0,10);
          if (0x100 < uVar11) {
            iVar3 = FUN_0016b374(uVar11,2,0,0x100);
            goto LAB_00170434;
          }
          break;
        case '\x04':
          uVar13 = simple_strtol(iVar2,0,10);
          if (0x100 < uVar13) {
            iVar3 = FUN_0016b374(uVar13,3,0,0x100);
            goto LAB_00170434;
          }
          break;
        case '\x05':
          uVar5 = simple_strtol(iVar2,0,10);
          if (0x100 < uVar5) {
            iVar3 = FUN_0016b374(uVar5,4,0,0x100);
            goto LAB_00170434;
          }
          break;
        default:
          goto LAB_00170464;
        }
        uVar1 = (undefined1)uVar5;
        uVar12 = (undefined1)uVar13;
        uVar10 = (undefined1)uVar11;
        uVar8 = (undefined1)uVar9;
        uVar6 = (undefined1)uVar7;
        iVar2 = rstrtok(0,&_LC44);
        if (iVar2 == 0) goto LAB_001704b8;
LAB_0017036c:
        cVar4 = cVar4 + '\x01';
      } while( true );
    }
    cVar4 = '\0';
    uVar1 = 0;
    uVar6 = 0;
    uVar8 = 0;
    uVar10 = 0;
    uVar12 = 0;
LAB_001704b8:
    if (local_3b == cVar4) {
      local_30 = uVar6;
      local_2f = uVar8;
      local_2e = uVar10;
      local_2d = uVar12;
      local_2c = uVar1;
      iVar2 = SrCmdSRUpdateIBPD(param_1,&local_3c);
      if (iVar2 != 1) {
        return iVar2;
      }
    }
    else {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Format Error! ArgNum = %d != %d\n","SetSrIBPDAll",cVar4);
    }
  }
LAB_0017048c:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set sribpd=[InterBssByHdrBssid]-[InterBssByMu]-[InterBssByPbssColor]-[InterBssByPaid]-[InterBssByBssColor]\n"
           ,"SetSrIBPDAll");
  }
  return 1;
LAB_00170464:
  if (-1 < DebugLevel) {
    printk("%s: set wrong parameters\n","SetSrIBPDAll");
  }
  rstrtok(0,&_LC44);
  goto LAB_0017048c;
}

