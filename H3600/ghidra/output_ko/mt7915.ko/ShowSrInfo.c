// module: mt7915.ko
// function: ShowSrInfo @ 0x16bfc0
// size: 612 bytes
//

int ShowSrInfo(int *param_1,int param_2)

{
  undefined1 uVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  undefined1 local_24;
  char local_23;
  undefined1 local_22;
  byte local_20;
  byte local_1f;
  
  iVar4 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar4 == 0) {
    return 1;
  }
  uVar1 = HcGetBandByWdev(iVar4);
  os_zero_mem(&local_24,0xc);
  local_24 = 0x21;
  local_23 = '\x02';
  local_22 = uVar1;
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Arg is Null\n","ShowSrInfo");
    }
  }
  else {
    iVar4 = rstrtok(param_2,&_LC44);
    if (iVar4 != 0) {
      bVar2 = 0;
      cVar6 = '\x01';
      bVar3 = 0;
      do {
        if (cVar6 == '\x01') {
          bVar3 = simple_strtol(iVar4,0,10);
          if (bVar3 < 0x10) goto LAB_0016c064;
          iVar5 = FUN_0016b374(bVar3,0,0,0xf);
LAB_0016c0c0:
          iVar4 = rstrtok(0,&_LC44);
          if (iVar4 == 0) {
            if (iVar5 != 1) goto LAB_0016c158;
            goto LAB_0016c118;
          }
          if (iVar5 == 1) goto LAB_0016c118;
        }
        else {
          if (cVar6 != '\x02') {
            if (-1 < DebugLevel) {
              printk("%s: set wrong parameters\n","ShowSrInfo",10);
            }
            rstrtok(0,&_LC44);
            goto LAB_0016c118;
          }
          bVar2 = simple_strtol(iVar4,0);
          if (0x20 < bVar2) {
            iVar5 = FUN_0016b374(bVar2,1,0,0x20);
            goto LAB_0016c0c0;
          }
LAB_0016c064:
          iVar4 = rstrtok(0,&_LC44);
          if (iVar4 == 0) goto LAB_0016c158;
        }
        cVar6 = cVar6 + '\x01';
      } while( true );
    }
    cVar6 = '\0';
    bVar2 = 0;
    bVar3 = 0;
LAB_0016c158:
    if (local_23 == cVar6) {
      local_20 = bVar3;
      local_1f = bVar2;
      iVar4 = SrCmd(param_1,&local_24);
      if (iVar4 == 0) {
        return 0;
      }
      goto LAB_0016c11c;
    }
    if (-1 < DebugLevel) {
      printk("%s: Format Error! ArgNum = %d != %d\n","ShowSrInfo",cVar6);
    }
  }
LAB_0016c118:
  iVar4 = 1;
LAB_0016c11c:
  if (-1 < DebugLevel) {
    printk("%s: iwpriv ra0 show srinfo=0-0\n","ShowSrInfo");
  }
  return iVar4;
}

