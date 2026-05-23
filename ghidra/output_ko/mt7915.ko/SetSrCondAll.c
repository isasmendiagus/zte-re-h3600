// module: mt7915.ko
// function: SetSrCondAll @ 0x16f294
// size: 512 bytes
//

int SetSrCondAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  undefined1 uVar7;
  uint uVar8;
  undefined1 uVar9;
  uint uVar10;
  undefined1 uVar11;
  uint uVar12;
  undefined1 uVar13;
  uint uVar14;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  undefined1 local_40;
  char local_3f;
  undefined1 local_3e;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev();
  os_zero_mem(&local_40);
  local_40 = 7;
  local_3f = '\n';
  local_3e = uVar1;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrCondAll");
  }
  else {
    iVar2 = rstrtok(param_2,&_LC44);
    if (iVar2 != 0) {
      uVar4 = 0;
      cVar6 = '\x01';
      uVar5 = 0;
      uVar8 = 0;
      uVar10 = 0;
      uVar14 = 0;
      uVar12 = 0;
      local_54 = 0;
      local_50 = 0;
      local_4c = 0;
      local_48 = 0;
      do {
        uVar1 = (undefined1)uVar5;
        uVar7 = (undefined1)uVar8;
        uVar9 = (undefined1)uVar10;
        uVar13 = (undefined1)uVar14;
        uVar11 = (undefined1)uVar12;
        switch(cVar6) {
        case '\x01':
          uVar12 = simple_strtol(iVar2,0,10);
          if (1 < uVar12) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",0,uVar12);
            }
            goto LAB_0016f620;
          }
          break;
        case '\x02':
          uVar14 = simple_strtol(iVar2,0,10);
          if (1 < uVar14) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",1,uVar14);
            }
            goto LAB_0016f620;
          }
          break;
        case '\x03':
          uVar10 = simple_strtol(iVar2,0,10);
          if (1 < uVar10) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",2,uVar10);
            }
            goto LAB_0016f620;
          }
          break;
        case '\x04':
          uVar8 = simple_strtol(iVar2,0,10);
          if (1 < uVar8) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",3,uVar8);
            }
            goto LAB_0016f620;
          }
          break;
        case '\x05':
          local_48 = simple_strtol(iVar2,0,10);
          if (1 < local_48) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",4,local_48);
            }
            goto LAB_0016f620;
          }
          break;
        case '\x06':
          local_4c = simple_strtol(iVar2,0,10);
          if (1 < local_4c) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",5,local_4c);
            }
            goto LAB_0016f620;
          }
          break;
        case '\a':
          local_50 = simple_strtol(iVar2,0,10);
          if (1 < local_50) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",6,local_50);
            }
            goto LAB_0016f620;
          }
          break;
        case '\b':
          local_54 = simple_strtol(iVar2,0,10);
          if (1 < local_54) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",7,local_54);
            }
            goto LAB_0016f620;
          }
          break;
        case '\t':
          uVar5 = simple_strtol(iVar2,0,10);
          if (1 < uVar5) {
            if (-1 < DebugLevel) {
              printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",8,uVar5);
            }
            goto LAB_0016f620;
          }
          break;
        case '\n':
          uVar4 = simple_strtol(iVar2,0,10);
          if (uVar4 < 0x100) break;
          iVar3 = FUN_0016b374(uVar4,9,0,0xff);
          iVar2 = rstrtok(0,&_LC44);
          if (iVar2 != 0) {
            if (iVar3 != 1) goto LAB_0016f39c;
            goto LAB_0016f634;
          }
          if (iVar3 == 1) goto LAB_0016f634;
          goto LAB_0016f684;
        default:
          goto LAB_0016f60c;
        }
        uVar1 = (undefined1)uVar5;
        uVar7 = (undefined1)uVar8;
        uVar9 = (undefined1)uVar10;
        uVar13 = (undefined1)uVar14;
        uVar11 = (undefined1)uVar12;
        iVar2 = rstrtok(0,&_LC44);
        if (iVar2 == 0) goto LAB_0016f684;
LAB_0016f39c:
        cVar6 = cVar6 + '\x01';
      } while( true );
    }
    uVar4 = 0;
    uVar1 = 0;
    cVar6 = '\0';
    uVar7 = 0;
    uVar9 = 0;
    uVar11 = 0;
    uVar13 = 0;
    local_54._0_1_ = 0;
    local_50._0_1_ = 0;
    local_4c._0_1_ = 0;
    local_48._0_1_ = 0;
LAB_0016f684:
    if (local_3f == cVar6) {
      local_30 = (undefined1)local_48;
      local_2f = (undefined1)local_4c;
      local_2b = (undefined1)uVar4;
      local_2e = (undefined1)local_50;
      local_2d = (undefined1)local_54;
      local_34 = uVar11;
      local_33 = uVar13;
      local_32 = uVar9;
      local_31 = uVar7;
      local_2c = uVar1;
      iVar2 = SrCmdSRUpdateCond(param_1,&local_40);
      if (iVar2 != 1) {
        return iVar2;
      }
    }
    else {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Format Error! ArgNum = %d != %d\n","SetSrCondAll",cVar6);
    }
  }
LAB_0016f634:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set srcond=[SrRcpiCckRateEn]-[SrMacRcpiRateEn]-[SrRxvRcpiRateEn]-[SrRcpiHeRateEn]-[u4SrRcpiVhtRateEn]-[SrRcpiHtRateEn]-[SrRcpiLgRateEn]-[SrRxvEntry]-[SrPeriodLimitEn]-[SrPeriodLimit]\n"
           ,"SetSrCondAll");
  }
  return 1;
LAB_0016f60c:
  if (-1 < DebugLevel) {
    printk("%s: set wrong parameters\n","SetSrCondAll");
  }
LAB_0016f620:
  rstrtok(0,&_LC44);
  goto LAB_0016f634;
}

