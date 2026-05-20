// module: mt7915.ko
// function: Set_ClearSiteSurvey_Proc @ 0xba504
// size: 392 bytes
//

undefined4
Set_ClearSiteSurvey_Proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  size_t sVar2;
  int iVar3;
  
  iVar3 = *param_1;
  sVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  sVar2 = strlen(param_2);
  if (sVar2 < 2) {
    sVar2 = sVar1;
  }
  if (sVar2 != 1) {
    if (-1 < DebugLevel) {
      printk("Wrong argument type/Value\n");
      return 0;
    }
    return 0;
  }
  if ((param_1[0x28e7e1] & 2U) == 0) {
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
    return 0xffffff9c;
  }
  if ((param_1[0x28e7e1] & 0x4000U) == 0) {
    iVar3 = get_scan_ctrl_by_wdev
                      (param_1,param_1 + (uint)*(byte *)(iVar3 + 0x3c) * 0x160d + 0xadc92);
    if (((*(uint *)(iVar3 + 0x17c) & 0xff00ff) == 1) || (*(char *)(iVar3 + 0x17c) == '\0')) {
      BssTableInit(param_1 + 0x261f88);
      if (DebugLevel < 3) {
        return 1;
      }
      printk("Clear the Scan table\n");
    }
    if (2 < DebugLevel) {
      printk("Set_ClearSiteSurvey_Proc\n");
    }
    return 1;
  }
  if (2 < DebugLevel) {
    printk("%s: Scan in Progress!\n","Set_ClearSiteSurvey_Proc");
    return 0xffffffea;
  }
  return 0xffffffea;
}

