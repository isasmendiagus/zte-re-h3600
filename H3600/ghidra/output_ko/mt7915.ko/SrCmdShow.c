// module: mt7915.ko
// function: SrCmdShow @ 0x16c228
// size: 336 bytes
//

undefined4 SrCmdShow(int *param_1,int param_2,undefined1 param_3,char param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  undefined1 local_24;
  char local_23;
  undefined1 local_22;
  undefined4 local_1c;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 != 0) {
    uVar1 = HcGetBandByWdev();
    os_zero_mem(&local_24,0xc);
    local_24 = param_3;
    local_23 = param_4;
    local_22 = uVar1;
    if (param_2 == 0) {
      if (-1 < DebugLevel) {
        printk("%s: Arg is Null\n","SrCmdShow");
        return 1;
      }
    }
    else {
      iVar2 = rstrtok(param_2,&_LC44);
      cVar4 = '\0';
      if (iVar2 != 0) {
        local_1c = simple_strtol(iVar2,0,10);
        iVar2 = rstrtok(0,&_LC44);
        if (iVar2 != 0) {
          if (-1 < DebugLevel) {
            printk("%s: set wrong parameters\n","SrCmdShow");
          }
          rstrtok(0,&_LC44);
          return 1;
        }
        cVar4 = '\x01';
      }
      if (local_23 == cVar4) {
        uVar3 = SrCmd(param_1,&local_24);
        return uVar3;
      }
      if (-1 < DebugLevel) {
        printk("%s: Format Error! ArgNum = %d != %d\n","SrCmdShow");
      }
    }
  }
  return 1;
}

