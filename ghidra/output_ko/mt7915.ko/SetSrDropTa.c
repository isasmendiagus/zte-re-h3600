// module: mt7915.ko
// function: SetSrDropTa @ 0x16e9dc
// size: 596 bytes
//

int SetSrDropTa(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined1 local_2b4;
  char local_2b3;
  undefined1 local_2b2;
  undefined1 local_2b0;
  undefined4 local_2a4;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 != 0) {
    uVar1 = HcGetBandByWdev();
    os_zero_mem(&local_2b4,0x294);
    local_2b4 = 4;
    local_2b3 = '\x02';
    local_2b2 = uVar1;
    if (param_2 == 0) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Arg is Null\n","SetSrDropTa");
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
            if (uVar5 < 0x10) {
              iVar2 = rstrtok(0,&_LC44);
              iVar4 = 0;
              if (iVar2 == 0) goto LAB_0016ead8;
            }
            else {
              iVar4 = FUN_0016b374(uVar5,0,0,0xf);
              iVar2 = rstrtok(0,&_LC44);
              if (iVar2 == 0) {
LAB_0016ebb4:
                if (iVar4 == 1) goto LAB_0016eb2c;
                goto LAB_0016ead8;
              }
              if (iVar4 == 1) goto LAB_0016eb2c;
            }
          }
          else {
            if (cVar3 != '\x02') {
              if (-1 < DebugLevel) {
                printk("%s: set wrong parameters\n","SetSrDropTa",0x10);
              }
              rstrtok(0,&_LC44);
              goto LAB_0016eb2c;
            }
            uVar6 = simple_strtol(iVar2,0);
            iVar2 = rstrtok(0,&_LC44);
            if (iVar2 == 0) goto LAB_0016ebb4;
          }
          cVar3 = cVar3 + '\x01';
        } while( true );
      }
      cVar3 = '\0';
      uVar5 = 0;
      uVar6 = 0;
LAB_0016ead8:
      if (local_2b3 == cVar3) {
        local_2b0 = (undefined1)uVar5;
        local_2a4 = uVar6;
        iVar2 = SrCmdSRUpdateGloVarSingleDropTa(param_1,&local_2b4,uVar5,0);
        if (iVar2 != 1) {
          return iVar2;
        }
      }
      else {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s: Format Error! ArgNum = %d != %d\n","SetSrDropTa",cVar3);
      }
    }
LAB_0016eb2c:
    if (-1 < DebugLevel) {
      printk("%s: iwpriv ra0 set srdropta=[u4DropTaIdx]-[u4Address2]\n","SetSrDropTa");
    }
  }
  return 1;
}

