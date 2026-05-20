// module: mt7915.ko
// function: SetSrCapSrEn @ 0x16dbf0
// size: 444 bytes
//

int SetSrCapSrEn(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  undefined1 local_28;
  char local_27;
  undefined1 local_26;
  undefined1 local_1c;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev();
  os_zero_mem(&local_28,0x18);
  local_28 = 1;
  local_27 = '\x01';
  local_26 = uVar1;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Arg is Null\n","SetSrCapSrEn");
    goto LAB_0016dca0;
  }
  iVar2 = rstrtok(param_2,&_LC44);
  if (iVar2 == 0) {
    cVar4 = '\0';
    uVar3 = 0;
LAB_0016dd08:
    if (local_27 == cVar4) {
      local_1c = (undefined1)uVar3;
      iVar2 = SrCmdSRUpdateCap(param_1,&local_28);
      if (iVar2 != 1) {
        return iVar2;
      }
    }
    else {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Format Error! ArgNum = %d != %d\n","SetSrCapSrEn");
    }
  }
  else {
    uVar3 = simple_strtol(iVar2,0,10);
    if (uVar3 < 2) {
      iVar2 = rstrtok(0,&_LC44);
      if (iVar2 == 0) {
        cVar4 = '\x01';
        goto LAB_0016dd08;
      }
      if (-1 < DebugLevel) {
        printk("%s: set wrong parameters\n","SetSrCapSrEn");
      }
    }
    else if (-1 < DebugLevel) {
      printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",0,uVar3);
    }
    rstrtok(0,&_LC44);
  }
LAB_0016dca0:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 set srcapsren=[SrEn]\n","SetSrCapSrEn");
  }
  return 1;
}

