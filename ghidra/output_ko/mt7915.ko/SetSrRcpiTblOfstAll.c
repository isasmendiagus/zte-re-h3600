// module: mt7915.ko
// function: SetSrRcpiTblOfstAll @ 0x16f9d0
// size: 472 bytes
//

int SetSrRcpiTblOfstAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  char cVar6;
  uint uVar7;
  undefined2 uVar8;
  uint uVar9;
  undefined2 uVar10;
  uint uVar11;
  undefined2 uVar12;
  uint uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined1 local_44;
  char local_43;
  undefined1 local_42;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  
  iVar3 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar3 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev();
  os_zero_mem(&local_44,0x1c);
  local_44 = 9;
  local_43 = '\a';
  local_42 = uVar1;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrRcpiTblOfstAll");
  }
  else {
    iVar3 = rstrtok(param_2,&_LC44);
    if (iVar3 != 0) {
      uVar2 = 0;
      cVar6 = '\x01';
      uVar7 = 0;
      uVar11 = 0;
      uVar13 = 0;
      uVar9 = 0;
      uVar15 = 0;
      uVar14 = 0;
      do {
        cVar5 = cVar6 + -1;
        switch(cVar5) {
        case '\0':
          uVar9 = simple_strtol(iVar3,0,10,cVar5,uVar14,uVar15);
          if (uVar9 < 0x1001) break;
          iVar4 = FUN_0016b374(uVar9,0,0,0x1000);
LAB_0016fbf0:
          uVar10 = (undefined2)uVar11;
          uVar12 = (undefined2)uVar13;
          uVar8 = (undefined2)uVar9;
          iVar3 = rstrtok(0,&_LC44);
          if (iVar3 != 0) {
            if (iVar4 != 1) goto LAB_0016fac0;
            goto LAB_0016fc48;
          }
          if (iVar4 == 1) goto LAB_0016fc48;
          goto LAB_0016fc74;
        case '\x01':
          uVar13 = simple_strtol(iVar3,0,10,cVar5,uVar14,uVar15);
          if (0x10 < uVar13) {
            iVar4 = FUN_0016b374(uVar13,1,0,0x10);
            goto LAB_0016fbf0;
          }
          break;
        case '\x02':
          uVar11 = simple_strtol(iVar3,0,10,cVar5,uVar14,uVar15);
          if (0x1000 < uVar11) {
            iVar4 = FUN_0016b374(uVar11,2,0,0x1000);
            goto LAB_0016fbf0;
          }
          break;
        case '\x03':
          uVar7 = simple_strtol(iVar3,0,10,cVar5,uVar14,uVar15);
          if (0x10 < uVar7) {
            iVar4 = FUN_0016b374(uVar7,3,0,0x10);
            goto LAB_0016fbf0;
          }
          break;
        case '\x04':
          uVar14 = simple_strtol(iVar3,0,10,cVar5,uVar14,uVar15);
          if (0x100 < uVar7) {
            iVar4 = FUN_0016b374(uVar7,4,0,0x100);
            goto LAB_0016fbf0;
          }
          break;
        case '\x05':
          uVar15 = simple_strtol(iVar3,0,10,cVar5,uVar14,uVar15);
          if (0x100 < uVar7) {
            iVar4 = FUN_0016b374(uVar7,5,0,0x100);
            goto LAB_0016fbf0;
          }
          break;
        case '\x06':
          uVar2 = simple_strtol(iVar3,0,10,cVar5,uVar14,uVar15);
          if (0x100 < uVar7) {
            iVar4 = FUN_0016b374(uVar7,6,0,0x100);
            goto LAB_0016fbf0;
          }
          break;
        default:
          goto LAB_0016fc20;
        }
        uVar10 = (undefined2)uVar11;
        uVar12 = (undefined2)uVar13;
        uVar8 = (undefined2)uVar9;
        iVar3 = rstrtok(0,&_LC44);
        if (iVar3 == 0) goto LAB_0016fc74;
LAB_0016fac0:
        cVar6 = cVar6 + '\x01';
      } while( true );
    }
    cVar6 = '\0';
    uVar7 = 0;
    uVar2 = 0;
    uVar8 = 0;
    uVar10 = 0;
    uVar12 = 0;
    uVar14 = 0;
    uVar15 = 0;
LAB_0016fc74:
    if (local_43 == cVar6) {
      local_30 = (undefined2)uVar14;
      local_2e = (undefined2)uVar15;
      local_32 = (undefined2)uVar7;
      local_38 = uVar8;
      local_36 = uVar12;
      local_34 = uVar10;
      local_2c = uVar2;
      iVar3 = SrCmdSRUpdateRcpiTblOfst(param_1,&local_44);
      if (iVar3 != 1) {
        return iVar3;
      }
    }
    else {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Format Error! ArgNum = %d != %d\n","SetSrRcpiTblOfstAll",cVar6,local_43,uVar14,
             uVar15);
    }
  }
LAB_0016fc48:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set srrcpitblofst=[RxBwRcpiOfst]-[StbcRcpiOfst]-[NumAntRcpiOfst]-[LdpcRcpiOfst]-[DcmRcpiOfst]-[MacRcpiOfst]-[SigRcpiOfst]\n"
           ,"SetSrRcpiTblOfstAll");
  }
  return 1;
LAB_0016fc20:
  if (-1 < DebugLevel) {
    printk("%s: set wrong parameters\n","SetSrRcpiTblOfstAll");
  }
  rstrtok(0,&_LC44);
  goto LAB_0016fc48;
}

