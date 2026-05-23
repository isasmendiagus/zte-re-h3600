// module: mt7915.ko
// function: Set_SiteSurvey_Proc @ 0xba20c
// size: 760 bytes
//

undefined4 Set_SiteSurvey_Proc(int *param_1,char *param_2)

{
  int *piVar1;
  undefined4 uVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  size_t local_44;
  undefined1 auStack_40 [36];
  
  if ((param_1 == (int *)0x0) || (iVar4 = *param_1, iVar4 == 0)) {
    if (-1 < DebugLevel) {
      printk("Set_SiteSurvey_Proc para error pAdapter =%p\n",param_1);
    }
    return 0;
  }
  piVar1 = (int *)get_wdev_by_ioctl_idx_and_iftype
                            (param_1,*(undefined4 *)(iVar4 + 0x3c),*(undefined4 *)(iVar4 + 0x38));
  if (piVar1 == (int *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Set_SiteSurvey_Proc para error wdev =%p\n",0);
    uVar2 = 0;
  }
  else {
    HcGetBandByWdev();
    iVar4 = *param_1;
    if ((param_1[0x28e7e1] & 2U) == 0) {
      if (DebugLevel < 3) {
        uVar2 = 0xffffff9c;
      }
      else {
        printk("INFO::Network is down!\n");
        uVar2 = 0xffffff9c;
      }
    }
    else {
      uVar5 = (uint)*(byte *)((int)param_1 + 0x286285);
      if (uVar5 == 1) {
        if (*(int *)(iVar4 + 0x38) == 0x400) {
          piVar1 = param_1 + (*(uint *)(iVar4 + 0x3c) & 0xff) * 0x84dec + 0xdb6d6;
        }
        else if (*(int *)(iVar4 + 0x38) == 0x200) {
          piVar1 = param_1 + (*(uint *)(iVar4 + 0x3c) & 0xff) * 0x160d + 0xadc92;
        }
        else {
          piVar1 = param_1 + 0xadc92;
        }
      }
      else if (uVar5 == 0) {
        if ((char)param_1[0xa6e43] == '\x01') {
          if (2 < DebugLevel) {
            printk("!!! Driver is in Monitor Mode now !!!\n");
            return 0xffffffea;
          }
          return 0xffffffea;
        }
        __memzero(&local_44,0x24);
        local_44 = uVar5;
        if ((param_2 != (char *)0x0) && (sVar3 = strlen(param_2), sVar3 < 0x21)) {
          RTMPMoveMemory(auStack_40,param_2,sVar3);
          local_44 = strlen(param_2);
        }
        *(undefined1 *)((int)param_1 + *(int *)(iVar4 + 0x3c) * 0x2137b0 + 0x580ccd) = 1;
        StaSiteSurvey(param_1,&local_44,0,param_1 + *(int *)(iVar4 + 0x3c) * 0x84dec + 0xdb6d6);
        if (2 < DebugLevel) {
          printk("Set_SiteSurvey_Proc\n");
          return 1;
        }
        return 1;
      }
      __memzero(&local_44,0x24);
      if ((*param_2 == '\0') || (sVar3 = strlen(param_2), 0x20 < sVar3)) {
        local_44 = 0;
        ApSiteSurvey_by_wdev(param_1,&local_44,0x80,0,piVar1);
        uVar2 = 1;
      }
      else {
        memcpy(auStack_40,param_2,sVar3);
        local_44 = sVar3;
        ApSiteSurvey_by_wdev(param_1,&local_44,0,0,piVar1);
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}

