// module: mt7915.ko
// function: Set_ApScan_Proc @ 0xbab90
// size: 984 bytes
//

undefined4 Set_ApScan_Proc(int *param_1,char *param_2)

{
  undefined4 uVar1;
  size_t sVar2;
  int iVar3;
  char cVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 local_5c;
  char acStack_51 [8];
  char local_49 [37];
  
  iVar8 = *param_1;
  __memzero(acStack_51,8);
  __memzero(local_49,0x21);
  if ((param_1[0x28e7e1] & 2U) == 0) {
    if (DebugLevel < 3) {
      uVar1 = 0xffffff9c;
    }
    else {
      printk("INFO::Network is down!\n");
      uVar1 = 0xffffff9c;
    }
  }
  else {
    cVar4 = *param_2;
    if (cVar4 == '\0') {
      uVar7 = 0;
      local_5c = 0;
    }
    else {
      iVar6 = 0;
      uVar7 = 0;
      local_5c = 0;
      iVar3 = 0;
LAB_000babfc:
      do {
        param_2 = param_2 + 1;
        local_49[iVar3] = cVar4;
        if (cVar4 == ':') {
          iVar6 = iVar6 + 1;
          if (iVar6 == 1) {
            local_49[iVar3] = '\0';
            if ((local_49[0] == '\0') || (sVar2 = strlen(local_49), 7 < sVar2)) {
LAB_000baed8:
              if (DebugLevel < 0) {
                return 0;
              }
              printk("wrong scan type argument\n");
              return 0;
            }
            strncpy(acStack_51,local_49,7);
            iVar3 = strcmp(acStack_51,"active");
            if (iVar3 == 0) {
              cVar4 = *param_2;
              iVar9 = 0;
            }
            else {
              iVar3 = strcmp(acStack_51,"passive");
              if (iVar3 != 0) goto LAB_000baed8;
              cVar4 = *param_2;
              iVar9 = 0;
            }
          }
          else if (iVar6 == 2) {
            local_49[iVar3] = '\0';
            if ((local_49[0] == '\0') || (sVar2 = strlen(local_49), 3 < sVar2)) {
LAB_000baeb0:
              if (-1 < DebugLevel) {
                printk("wrong channel number\n");
                return 0;
              }
              return 0;
            }
            uVar7 = simple_strtol(local_49,0,10);
            iVar3 = ChannelSanity(param_1,uVar7 & 0xff);
            if (iVar3 == 0) goto LAB_000baeb0;
            cVar4 = *param_2;
            iVar9 = 0;
          }
          else {
            if (2 < iVar6) {
              if (-1 < DebugLevel) {
                printk("wrong number of arguments\n");
                return 0;
              }
              return 0;
            }
            iVar9 = iVar3 + 1;
            cVar4 = *param_2;
          }
        }
        else {
          cVar4 = *param_2;
          if (cVar4 != '\0') {
            iVar3 = iVar3 + 1;
            goto LAB_000babfc;
          }
          iVar9 = iVar3 + 1;
          local_49[iVar3 + 1] = '\0';
          if (local_49[0] == '\0') break;
          sVar2 = strlen(local_49);
          if (10 < sVar2) {
LAB_000bad98:
            if (-1 < DebugLevel) {
              printk("wrong Timeout value\n");
              return 0;
            }
            return 0;
          }
          iVar3 = simple_strtol(local_49,0,10);
          if (iVar3 == -1) {
            if (local_49[0] != '\0') goto LAB_000bad98;
            cVar4 = *param_2;
          }
          else {
            local_5c = simple_strtol(local_49,0,10);
            cVar4 = *param_2;
          }
        }
        iVar3 = iVar9;
      } while (cVar4 != '\0');
    }
    piVar5 = param_1;
    if (*(int *)(iVar8 + 0x38) == 0x200) {
      piVar5 = param_1 + (*(uint *)(iVar8 + 0x3c) & 0xff) * 0x160d;
    }
    piVar5 = piVar5 + 0xadc92;
    iVar8 = get_scan_ctrl_by_wdev(param_1,piVar5);
    *(undefined1 *)(iVar8 + 0x4f) = 0;
    *(undefined1 *)(iVar8 + 0x55) = 1;
    *(undefined4 *)(iVar8 + 0x5c) = 1;
    *(undefined1 *)(iVar8 + 0x54) = 0;
    iVar8 = strcmp(acStack_51,"passive");
    if (iVar8 == 0) {
      ApSiteSurveyNew_by_wdev(param_1,uVar7,local_5c,0x80,0,piVar5);
    }
    else {
      iVar8 = strcmp(acStack_51,"active");
      if (iVar8 == 0) {
        ApSiteSurveyNew_by_wdev(param_1,uVar7,local_5c,0,0,piVar5);
      }
    }
    if (DebugLevel < 3) {
      uVar1 = 1;
    }
    else {
      printk("Set_ApScan_Proc\n");
      uVar1 = 1;
    }
  }
  return uVar1;
}

