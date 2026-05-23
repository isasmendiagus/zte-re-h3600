// module: mt7915.ko
// function: SetSrStaInit @ 0x16ef2c
// size: 588 bytes
//

int SetSrStaInit(int *param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  undefined1 local_2ac;
  char local_2ab;
  undefined1 local_2aa;
  undefined1 local_2a8;
  undefined1 local_2a7;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 != 0) {
    uVar1 = HcGetBandByWdev();
    os_zero_mem(&local_2ac,0x294);
    local_2ac = 6;
    local_2ab = '\x02';
    local_2aa = uVar1;
    if (param_2 == 0) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Arg is Null\n","SetSrStaInit");
    }
    else {
      iVar2 = rstrtok(param_2,&_LC44);
      if (iVar2 != 0) {
        uVar5 = 0;
        cVar4 = '\x01';
        uVar6 = 0;
        do {
          if (cVar4 == '\x01') {
            uVar6 = simple_strtol(iVar2,0,10);
            if (uVar6 < 0x10) goto LAB_0016efcc;
            iVar3 = FUN_0016b374(uVar6,0,0,0xf);
LAB_0016f024:
            iVar2 = rstrtok(0,&_LC44);
            if (iVar2 == 0) {
              if (iVar3 != 1) goto LAB_0016f0c4;
              goto LAB_0016f07c;
            }
            if (iVar3 == 1) goto LAB_0016f07c;
          }
          else {
            if (cVar4 != '\x02') {
              if (-1 < DebugLevel) {
                printk("%s: set wrong parameters\n","SetSrStaInit",10);
              }
              rstrtok(0,&_LC44);
              goto LAB_0016f07c;
            }
            uVar5 = simple_strtol(iVar2,0);
            if (0x20 < uVar5) {
              iVar3 = FUN_0016b374(uVar5,1,0,0x20);
              goto LAB_0016f024;
            }
LAB_0016efcc:
            iVar2 = rstrtok(0,&_LC44);
            if (iVar2 == 0) goto LAB_0016f0c4;
          }
          cVar4 = cVar4 + '\x01';
        } while( true );
      }
      cVar4 = '\0';
      uVar5 = 0;
      uVar6 = 0;
LAB_0016f0c4:
      if (local_2ab == cVar4) {
        local_2a8 = (undefined1)uVar6;
        local_2a7 = (undefined1)uVar5;
        iVar2 = SrCmdSRUpdateGloVarSingleDropTa(param_1,&local_2ac,uVar6,uVar5);
        if (iVar2 != 1) {
          return iVar2;
        }
      }
      else {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s: Format Error! ArgNum = %d != %d\n","SetSrStaInit",cVar4);
      }
    }
LAB_0016f07c:
    if (-1 < DebugLevel) {
      printk("%s: iwpriv ra0 set srstainit=[u4DropTaIdx]-[u4StaIdx]\n","SetSrStaInit");
    }
  }
  return 1;
}

