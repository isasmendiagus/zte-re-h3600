// module: mt7915.ko
// function: Set_RadioOn_Proc @ 0xba8b0
// size: 596 bytes
//

undefined4 Set_RadioOn_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  int *piVar5;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: wdev is NULL\n","Set_RadioOn_Proc");
      return 0;
    }
    return 0;
  }
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    piVar5 = param_1 + (uint)*(byte *)(iVar2 + 0xe) * 0x160d + 0xadc92;
    if (piVar5 == (int *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: pMbss is NULL\n","Set_RadioOn_Proc");
        return 0;
      }
      return 0;
    }
  }
  else {
    piVar5 = (int *)0x0;
  }
  cVar1 = os_str_tol(param_2,0,10);
  if (*(char *)(iVar2 + 0x28) == '\0') {
    if (-1 < DebugLevel) {
      puVar4 = &_LC131;
      if (cVar1 == '\0') {
        puVar4 = &_LC132;
      }
      printk("==>Set_RadioOn_Proc (%s) but IF is done, ignore!!! (wdev_idx %d)\n",puVar4,
             *(undefined1 *)(iVar2 + 0xc));
      return 1;
    }
  }
  else {
    iVar3 = IsHcRadioCurStatOffByChannel(param_1,*(undefined1 *)(iVar2 + 0x1a));
    if ((bool)cVar1 == (iVar3 == 0)) {
      if (-1 < DebugLevel) {
        puVar4 = &_LC131;
        if (cVar1 == '\0') {
          puVar4 = &_LC132;
        }
        printk("==>Set_RadioOn_Proc (%s) equal to current state, ignore!!! (wdev_idx %d)\n",puVar4,
               *(undefined1 *)(iVar2 + 0xc));
        return 1;
      }
    }
    else if (cVar1 == '\0') {
      cVar1 = *(char *)((int)param_1 + 0x286285);
      if (cVar1 == '\x01') {
        APStop(param_1,piVar5);
        cVar1 = *(char *)((int)param_1 + 0x286285);
      }
      if (cVar1 == '\0') {
        MSTAStop(param_1,iVar2);
      }
      MlmeRadioOff(param_1,iVar2);
      if (2 < DebugLevel) {
        printk("==>Set_RadioOn_Proc (OFF)\n");
      }
    }
    else {
      MlmeRadioOn(param_1,iVar2);
      if (2 < DebugLevel) {
        printk("==>Set_RadioOn_Proc (ON)\n");
      }
      if (*(char *)((int)param_1 + 0x286285) == '\x01') {
        APStartUp(param_1,piVar5,1);
        return 1;
      }
    }
  }
  return 1;
}

