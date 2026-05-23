// module: mt7915.ko
// function: SetSrSta @ 0x16ec34
// size: 464 bytes
//

int SetSrSta(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  undefined2 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined1 local_2b4;
  char local_2b3;
  undefined1 local_2b2;
  undefined1 local_2b0;
  undefined1 local_2af;
  undefined2 uStack_2a0;
  undefined1 auStack_29e [638];
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev();
  os_zero_mem(&local_2b4,0x294);
  local_2b4 = 5;
  local_2b3 = '\x04';
  local_2b2 = uVar1;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrSta");
  }
  else {
    iVar2 = rstrtok(param_2,&_LC44);
    if (iVar2 != 0) {
      uVar6 = 0;
      cVar4 = '\x01';
      uVar8 = 0;
      uVar7 = 0;
      uVar9 = 0;
      do {
        switch(cVar4) {
        case '\x01':
          uVar9 = simple_strtol(iVar2,0,10);
          if (uVar9 < 0x10) break;
          iVar3 = FUN_0016b374(uVar9,0,0,0xf);
LAB_0016eda4:
          uVar1 = (undefined1)uVar8;
          uVar5 = (undefined2)uVar6;
          iVar2 = rstrtok(0,&_LC44);
          if (iVar2 != 0) {
            if (iVar3 != 1) goto LAB_0016ed0c;
            goto LAB_0016edfc;
          }
          if (iVar3 == 1) goto LAB_0016edfc;
          goto LAB_0016ee28;
        case '\x02':
          uVar7 = simple_strtol(iVar2,0,10);
          if (0x1f < uVar7) {
            iVar3 = FUN_0016b374(uVar7,1,0,0x1f);
            goto LAB_0016eda4;
          }
          break;
        case '\x03':
          uVar6 = simple_strtol(iVar2,0,10);
          if (0x100 < uVar6) {
            iVar3 = FUN_0016b374(uVar6,2,0,0x100);
            goto LAB_0016eda4;
          }
          break;
        case '\x04':
          uVar8 = simple_strtol(iVar2,0,10);
          if (0xb < uVar8) {
            iVar3 = FUN_0016b374(uVar8,3,0,0xb);
            goto LAB_0016eda4;
          }
          break;
        default:
          goto LAB_0016edd4;
        }
        uVar1 = (undefined1)uVar8;
        uVar5 = (undefined2)uVar6;
        iVar2 = rstrtok(0,&_LC44);
        if (iVar2 == 0) goto LAB_0016ee28;
LAB_0016ed0c:
        cVar4 = cVar4 + '\x01';
      } while( true );
    }
    cVar4 = '\0';
    uVar5 = 0;
    uVar7 = 0;
    uVar1 = 0;
    uVar9 = 0;
LAB_0016ee28:
    if (local_2b3 == cVar4) {
      (&uStack_2a0)[uVar7 * 10] = uVar5;
      auStack_29e[uVar7 * 0x14 + 2] = uVar1;
      auStack_29e[uVar7 * 0x14] = 1;
      local_2b0 = (undefined1)uVar9;
      local_2af = (undefined1)uVar7;
      iVar2 = SrCmdSRUpdateGloVarSingleDropTa(param_1,&local_2b4,uVar9,uVar7);
      if (iVar2 != 1) {
        return iVar2;
      }
    }
    else {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Format Error! ArgNum = %d != %d\n","SetSrSta",cVar4);
    }
  }
LAB_0016edfc:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set srsta=[u4DropTaIdx]-[u4StaIdx]-[u4WlanId]-[u4SrRateOffset]\n",
           "SetSrSta");
  }
  return 1;
LAB_0016edd4:
  if (-1 < DebugLevel) {
    printk("%s: set wrong parameters\n","SetSrSta");
  }
  rstrtok(0,&_LC44);
  goto LAB_0016edfc;
}

