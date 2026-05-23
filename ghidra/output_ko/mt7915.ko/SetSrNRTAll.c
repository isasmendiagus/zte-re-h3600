// module: mt7915.ko
// function: SetSrNRTAll @ 0x1706c4
// size: 588 bytes
//

int SetSrNRTAll(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined1 local_38;
  char local_37;
  undefined1 local_36;
  undefined1 local_2c;
  undefined4 local_28;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 != 0) {
    uVar1 = HcGetBandByWdev();
    os_zero_mem(&local_38,0x18);
    local_38 = 0xc;
    local_37 = '\x02';
    local_36 = uVar1;
    if (param_2 == 0) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Arg is Null\n","SetSrNRTAll");
    }
    else {
      iVar2 = rstrtok(param_2,&_LC44);
      if (iVar2 != 0) {
        uVar6 = 0;
        cVar3 = '\x01';
        uVar5 = 0;
        iVar4 = 0;
        do {
          if (cVar3 == '\x01') {
            uVar5 = simple_strtol(iVar2,0,10);
            if (uVar5 < 0x11) {
              iVar2 = rstrtok(0,&_LC44);
              iVar4 = 0;
              if (iVar2 == 0) goto LAB_001707c0;
            }
            else {
              iVar4 = FUN_0016b374(uVar5,0,0,0x10);
              iVar2 = rstrtok(0,&_LC44);
              if (iVar2 == 0) {
LAB_0017089c:
                if (iVar4 == 1) goto LAB_00170814;
                goto LAB_001707c0;
              }
              if (iVar4 == 1) goto LAB_00170814;
            }
          }
          else {
            if (cVar3 != '\x02') {
              if (-1 < DebugLevel) {
                printk("%s: set wrong parameters\n","SetSrNRTAll",10);
              }
              rstrtok(0,&_LC44);
              goto LAB_00170814;
            }
            uVar6 = simple_strtol(iVar2,0);
            iVar2 = rstrtok(0,&_LC44);
            if (iVar2 == 0) goto LAB_0017089c;
          }
          cVar3 = cVar3 + '\x01';
        } while( true );
      }
      cVar3 = '\0';
      uVar5 = 0;
      uVar6 = 0;
LAB_001707c0:
      if (local_37 == cVar3) {
        local_2c = (undefined1)uVar5;
        local_28 = uVar6;
        iVar2 = SrCmdSRUpdateNRT(param_1,&local_38);
        if (iVar2 != 1) {
          return iVar2;
        }
      }
      else {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s: Format Error! ArgNum = %d != %d\n","SetSrNRTAll",cVar3);
      }
    }
LAB_00170814:
    if (-1 < DebugLevel) {
      printk("%s: iwpriv ra0 set srnrt=[TableIdx]-[NRTValue]\n","SetSrNRTAll");
    }
  }
  return 1;
}

