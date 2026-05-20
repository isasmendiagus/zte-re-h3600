// module: mt7915.ko
// function: RTMPIoctlConnStatus @ 0xe30d0
// size: 1208 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 RTMPIoctlConnStatus(int *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  char *pcVar6;
  int *piVar7;
  uint uVar8;
  
  iVar4 = *param_1;
  if (2 < DebugLevel) {
    printk("==>RTMPIoctlConnStatus\n");
  }
  if (*(int *)(iVar4 + 0x38) != 0x400) {
    return 0;
  }
  uVar8 = (uint)*(byte *)(iVar4 + 0x3c);
  piVar7 = param_1 + uVar8 * 0x84dec + 0xdb6d6;
  if (piVar7 == (int *)0x0) {
    return 0;
  }
  if (0 < DebugLevel) {
    printk("=============================================================\n");
  }
  iVar4 = GetAssociatedAPByWdev(param_1,piVar7);
  if ((iVar4 == 0) || (*(char *)((int)param_1 + uVar8 * 0x2137b0 + 0x57ff7e) == '\0')) {
LAB_000e3224:
    if (0 < DebugLevel) {
      printk("ApCli%d Connected AP : Disconnect\n",uVar8);
      goto LAB_000e33dc;
    }
    cVar1 = *(char *)((int)param_1 + 0x2b7242);
    iVar4 = DebugLevel;
joined_r0x000e3240:
    DebugLevel = iVar4;
    if (cVar1 == '\0') goto LAB_000e32f4;
LAB_000e3244:
    iVar3 = 0;
    iVar4 = DebugLevel;
    do {
      if ((piVar7 == *(int **)((int)param_1 + (int)(&DAT_003686ac + iVar3 * 8))) && (0 < iVar4)) {
        printk(&_LC597,iVar3);
        iVar4 = DebugLevel;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
  }
  else {
    bVar2 = false;
    piVar5 = param_1 + 0x28748;
    pcVar6 = (char *)((int)param_1 + 0x2f762);
    for (iVar4 = 0; iVar3 = HcGetMaxStaNum(param_1), iVar4 < iVar3; iVar4 = iVar4 + 1) {
      if (*piVar5 == 2) {
        if (((piVar5[0x3f] == 2) && (*pcVar6 == '\x01')) && (piVar7 == (int *)piVar5[2])) {
          if (DebugLevel < 1) {
LAB_000e3218:
            bVar2 = true;
          }
          else {
            printk("ApCli%d         Connected AP : %02x:%02x:%02x:%02x:%02x:%02x   SSID:%s\n",uVar8,
                   (char)piVar5[0x3b],*(undefined1 *)((int)piVar5 + 0xed),
                   *(undefined1 *)((int)piVar5 + 0xee),*(undefined1 *)((int)piVar5 + 0xef),
                   (char)piVar5[0x3c],*(undefined1 *)((int)piVar5 + 0xf1),
                   (int)param_1 + uVar8 * 0x2137b0 + 0x57ff5e);
            bVar2 = true;
            if ((char)param_1[uVar8 * 0x84dec + 0x15ffd0] == '\0') {
              if (DebugLevel < 1) goto LAB_000e3218;
              printk("MWDSCap : NO\n");
            }
            else {
              if (DebugLevel < 1) goto LAB_000e3218;
              printk("MWDSCap : YES\n");
            }
          }
        }
      }
      else if ((((*piVar5 == 0x40001) && (piVar5[0x3f] == 2)) && (*pcVar6 == '\x01')) &&
              (piVar7 == (int *)piVar5[2])) {
        if (DebugLevel < 1) goto LAB_000e3218;
        printk("Rept[wcid=%-3d] Connected AP : %02x:%02x:%02x:%02x:%02x:%02x   SSID:%s\n",iVar4,
               (char)piVar5[0x3b],*(undefined1 *)((int)piVar5 + 0xed),
               *(undefined1 *)((int)piVar5 + 0xee),*(undefined1 *)((int)piVar5 + 0xef),
               (char)piVar5[0x3c],*(undefined1 *)((int)piVar5 + 0xf1),
               (int)param_1 + uVar8 * 0x2137b0 + 0x57ff5e);
        bVar2 = true;
      }
      pcVar6 = pcVar6 + 0x620;
      piVar5 = piVar5 + 0x530;
    }
    if (!bVar2) goto LAB_000e3224;
LAB_000e33dc:
    if (DebugLevel < 1) {
      cVar1 = *(char *)((int)param_1 + 0x2b7242);
      iVar4 = DebugLevel;
      goto joined_r0x000e3240;
    }
    printk("ApCli%d CliLinkMap ra:",uVar8);
    iVar4 = DebugLevel;
    if (*(char *)((int)param_1 + 0x2b7242) != '\0') goto LAB_000e3244;
  }
  if ((0 < iVar4) && (printk(&_LC598), iVar4 = DebugLevel, 0 < DebugLevel)) {
    printk("Ignore repeater MAC address\n\r");
    iVar4 = DebugLevel;
  }
LAB_000e32f4:
  iVar3 = 0;
  pcVar6 = (char *)((int)param_1 + 0x368127);
  do {
    if ((*pcVar6 != '\0') && (0 < iVar4)) {
      printk("[%d]%02x:%02x:%02x:%02x:%02x:%02x\n\r",iVar3,pcVar6[-7],pcVar6[-6],pcVar6[-5],
             pcVar6[-4],pcVar6[-3],pcVar6[-2]);
      iVar4 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
    pcVar6 = pcVar6 + 0xc;
  } while (iVar3 != 0x20);
  if (0 < iVar4) {
    printk(&_LC598);
    if (DebugLevel < 1) {
      return 1;
    }
    printk("=============================================================\n");
    iVar4 = DebugLevel;
  }
  if (2 < iVar4) {
    printk("<==RTMPIoctlConnStatus\n");
    return 1;
  }
  return 1;
}

