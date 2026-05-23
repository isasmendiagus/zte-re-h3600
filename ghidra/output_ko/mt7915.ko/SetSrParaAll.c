// module: mt7915.ko
// function: SetSrParaAll @ 0x16e44c
// size: 504 bytes
//

/* WARNING: Type propagation algorithm not settling */

int SetSrParaAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  char cVar5;
  uint uVar6;
  undefined2 uVar7;
  int iVar8;
  undefined2 uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  undefined1 local_48;
  char local_47;
  undefined1 local_46;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined2 local_38;
  undefined2 local_36;
  uint local_34;
  uint local_30;
  undefined1 local_2c;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev();
  os_zero_mem(&local_48,0x20);
  local_48 = 3;
  local_47 = '\t';
  local_46 = uVar1;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrParaAll");
  }
  else {
    iVar2 = rstrtok(param_2,&_LC44);
    if (iVar2 != 0) {
      uVar6 = 0;
      cVar5 = '\x01';
      uVar12 = 0;
      uVar11 = 0;
      iVar10 = 0;
      iVar8 = 0;
      uVar16 = 0;
      uVar15 = 0;
      iVar14 = 0;
      iVar13 = 0;
      do {
        cVar4 = cVar5 + -1;
        switch(cVar4) {
        case '\0':
          iVar2 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          iVar13 = -iVar2;
          if (iVar2 - 0x3eU < 0x31) break;
          iVar3 = FUN_0016b374(iVar13,0,0xffffff92,0xffffffc2);
LAB_0016e71c:
          uVar1 = (undefined1)uVar6;
          uVar9 = (undefined2)iVar10;
          uVar7 = (undefined2)iVar8;
          iVar2 = rstrtok(0,&_LC44);
          if (iVar2 != 0) {
            if (iVar3 != 1) goto LAB_0016e54c;
            goto LAB_0016e774;
          }
          if (iVar3 != 1) goto LAB_0016e7a0;
          goto LAB_0016e774;
        case '\x01':
          iVar2 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          iVar14 = -iVar2;
          if (0x30 < iVar2 - 0x3eU) {
            iVar3 = FUN_0016b374(iVar14,1,0xffffff92,0xffffffc2);
            goto LAB_0016e71c;
          }
          break;
        case '\x02':
          uVar15 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          if (0x3f < uVar15) {
            iVar3 = FUN_0016b374(uVar15,2,0,0x3f);
            goto LAB_0016e71c;
          }
          break;
        case '\x03':
          uVar16 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          if (3 < uVar16) {
            iVar3 = FUN_0016b374(uVar16,3,0,3);
            goto LAB_0016e71c;
          }
          break;
        case '\x04':
          iVar2 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          iVar8 = -iVar2;
          if (iVar2 != 0 && -1 < iVar8 || iVar8 < -0x7f) {
            iVar3 = FUN_0016b374(iVar8,4,0xffffff81,0);
            goto LAB_0016e71c;
          }
          break;
        case '\x05':
          iVar2 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          iVar10 = -iVar2;
          if (iVar2 != 0 && -1 < iVar10 || iVar10 < -0x7f) {
            iVar3 = FUN_0016b374(iVar10,5,0xffffff81,0);
            goto LAB_0016e71c;
          }
          break;
        case '\x06':
          uVar11 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          if (1 < uVar11) {
            iVar3 = FUN_0016b374(uVar11,6,0,1);
            goto LAB_0016e71c;
          }
          break;
        case '\a':
          uVar12 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          if (2 < uVar12) {
            iVar3 = FUN_0016b374(uVar12,7,0,2);
            goto LAB_0016e71c;
          }
          break;
        case '\b':
          uVar6 = simple_strtol(iVar2,0,10,cVar4,iVar13,iVar14,uVar15,uVar16);
          if (0x1e < uVar6) {
            iVar3 = FUN_0016b374(uVar6,8,0,0x1e);
            goto LAB_0016e71c;
          }
          break;
        default:
          goto LAB_0016e74c;
        }
        uVar1 = (undefined1)uVar6;
        uVar9 = (undefined2)iVar10;
        uVar7 = (undefined2)iVar8;
        iVar2 = rstrtok(0,&_LC44);
        if (iVar2 == 0) goto LAB_0016e7a0;
LAB_0016e54c:
        cVar5 = cVar5 + '\x01';
      } while( true );
    }
    cVar5 = '\0';
    uVar1 = 0;
    uVar7 = 0;
    uVar9 = 0;
    uVar11 = 0;
    uVar12 = 0;
    iVar13 = 0;
    iVar14 = 0;
    uVar15 = 0;
    uVar16 = 0;
LAB_0016e7a0:
    if (local_47 == cVar5) {
      local_3c = (undefined1)iVar13;
      local_3b = (undefined1)iVar14;
      local_3a = (undefined1)uVar15;
      local_39 = (undefined1)uVar16;
      local_38 = uVar7;
      local_36 = uVar9;
      local_34 = uVar11;
      local_30 = uVar12;
      local_2c = uVar1;
      iVar2 = SrCmdSRUpdatePara(param_1,&local_48);
      if (iVar2 != 1) {
        return iVar2;
      }
    }
    else {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Format Error! ArgNum = %d != %d\n","SetSrParaAll",cVar5,local_47,iVar13,iVar14,
             uVar15,uVar16);
    }
  }
LAB_0016e774:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set srpara=[NonSrgPdThr]-[SrgPdThr]-[PeriodOfst]-[RcpiSourceSel]-[ObssPdMin]-[ObssPdMinSrg]-[RespTxPwrMode]-[TxPwrRestricMode]-[ObssTxPwrRef]\n"
           ,"SetSrParaAll");
  }
  return 1;
LAB_0016e74c:
  if (-1 < DebugLevel) {
    printk("%s: set wrong parameters\n","SetSrParaAll");
  }
  rstrtok(0,&_LC44);
  goto LAB_0016e774;
}

