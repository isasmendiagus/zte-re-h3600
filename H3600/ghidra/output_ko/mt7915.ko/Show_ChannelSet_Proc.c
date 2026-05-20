// module: mt7915.ko
// function: Show_ChannelSet_Proc @ 0x142084
// size: 1420 bytes
//

undefined4 Show_ChannelSet_Proc(int *param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  char *local_24;
  
  local_24 = param_2;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  pcVar2 = strsep(&local_24,":");
  pcVar3 = strsep(&local_24,":");
  pcVar4 = strsep(&local_24,":");
  if (pcVar4 == (char *)0x0 || (pcVar2 == (char *)0x0 || pcVar3 == (char *)0x0)) {
    if ((0 < DebugLevel) &&
       (printk(":%s: Invalid parameters\n","Show_ChannelSet_Proc"), 0 < DebugLevel)) {
      printk(":%s: TYPE:CHANNEL:ISAC\n","Show_ChannelSet_Proc");
    }
    return 0;
  }
  iVar5 = os_str_tol(pcVar2,0,10);
  uVar6 = os_str_tol(pcVar3,0,10);
  iVar7 = os_str_tol(pcVar4,0,10);
  if (DebugLevel < 1) {
    if (iVar5 == 0) {
LAB_001421f8:
      if (iVar7 == 1) {
        iVar1 = get_reg_table_by_country((int)param_1 + 0x794c31,0x20);
        pcVar2 = (char *)(iVar1 + 0x30);
        do {
          if (DebugLevel < 1) {
            iVar1 = DebugLevel;
            if (pcVar2[9] != '\0') {
LAB_00142394:
              pcVar3 = pcVar2 + 9;
              iVar1 = DebugLevel;
              do {
                if (0 < iVar1) {
                  printk("%-2d,");
                  iVar1 = DebugLevel;
                }
                pcVar3 = pcVar3 + 1;
              } while (*pcVar3 != '\0');
              goto LAB_001423ac;
            }
LAB_001423b4:
            if (pcVar2[0x19] != '\0') {
LAB_001423c0:
              pcVar3 = pcVar2 + 0x19;
              do {
                if (0 < iVar1) {
                  printk("%-2d,");
                  iVar1 = DebugLevel;
                }
                pcVar3 = pcVar3 + 1;
              } while (*pcVar3 != '\0');
              goto LAB_001423d8;
            }
          }
          else {
            printk("%-8d%-8d",*pcVar2,pcVar2[8]);
            iVar1 = DebugLevel;
            if (pcVar2[9] != '\0') goto LAB_00142394;
LAB_001423ac:
            if (iVar1 < 1) goto LAB_001423b4;
            printk(&_LC14);
            iVar1 = DebugLevel;
            if (pcVar2[0x19] != '\0') goto LAB_001423c0;
LAB_001423d8:
            if (0 < iVar1) {
              printk(&_LC13);
            }
          }
          pcVar2 = pcVar2 + 0x30;
          if (*pcVar2 == '\0') {
            return 1;
          }
        } while( true );
      }
      if (iVar7 == 2) {
        iVar1 = get_reg_table_by_country((int)param_1 + 0x794c31,0x1c0);
        pcVar2 = (char *)(iVar1 + 0x88);
        do {
          if (DebugLevel < 1) {
            iVar1 = DebugLevel;
            if (pcVar2[9] != '\0') {
LAB_00142304:
              pcVar3 = pcVar2 + 9;
              iVar1 = DebugLevel;
              do {
                if (0 < iVar1) {
                  printk("%-2d,");
                  iVar1 = DebugLevel;
                }
                pcVar3 = pcVar3 + 1;
              } while (*pcVar3 != '\0');
              goto LAB_0014231c;
            }
LAB_00142324:
            if (pcVar2[0x45] != '\0') {
LAB_00142330:
              pcVar3 = pcVar2 + 0x45;
              do {
                if (0 < iVar1) {
                  printk("%-2d,");
                  iVar1 = DebugLevel;
                }
                pcVar3 = pcVar3 + 1;
              } while (*pcVar3 != '\0');
              goto LAB_00142348;
            }
          }
          else {
            printk("%-8d%-8d",*pcVar2,pcVar2[8]);
            iVar1 = DebugLevel;
            if (pcVar2[9] != '\0') goto LAB_00142304;
LAB_0014231c:
            if (iVar1 < 1) goto LAB_00142324;
            printk(&_LC14);
            iVar1 = DebugLevel;
            if (pcVar2[0x45] != '\0') goto LAB_00142330;
LAB_00142348:
            if (0 < iVar1) {
              printk(&_LC13);
            }
          }
          pcVar2 = pcVar2 + 0x88;
          if (*pcVar2 == '\0') {
            return 1;
          }
        } while( true );
      }
      if (iVar7 == 0) {
        iVar1 = get_reg_table_by_country((int)param_1 + 0x794c31,0x10);
        pcVar2 = (char *)(iVar1 + 0x20);
        do {
          if (DebugLevel < 1) {
            if (pcVar2[9] != '\0') {
LAB_001422a0:
              pcVar3 = pcVar2 + 9;
              iVar1 = DebugLevel;
              do {
                if (0 < iVar1) {
                  printk("%-2d,");
                  iVar1 = DebugLevel;
                }
                pcVar3 = pcVar3 + 1;
              } while (*pcVar3 != '\0');
              goto LAB_001422b8;
            }
          }
          else {
            printk("%-8d%-8d",*pcVar2,pcVar2[8]);
            iVar1 = DebugLevel;
            if (pcVar2[9] != '\0') goto LAB_001422a0;
LAB_001422b8:
            if (0 < iVar1) {
              printk(&_LC13);
            }
          }
          pcVar2 = pcVar2 + 0x20;
          if (*pcVar2 == '\0') {
            return 1;
          }
        } while( true );
      }
      iVar1 = get_reg_table_by_country((int)param_1 + 0x794c31,0x10);
      pcVar2 = (char *)(iVar1 + 0x20);
      do {
        if (DebugLevel < 1) {
          if (pcVar2[9] != '\0') {
LAB_00142248:
            pcVar3 = pcVar2 + 9;
            iVar1 = DebugLevel;
            do {
              if (0 < iVar1) {
                printk("%-2d,");
                iVar1 = DebugLevel;
              }
              pcVar3 = pcVar3 + 1;
            } while (*pcVar3 != '\0');
            goto LAB_00142260;
          }
        }
        else {
          printk("%-8d%-8d",*pcVar2,pcVar2[8]);
          iVar1 = DebugLevel;
          if (pcVar2[9] != '\0') goto LAB_00142248;
LAB_00142260:
          if (0 < iVar1) {
            printk(&_LC13);
          }
        }
        pcVar2 = pcVar2 + 0x20;
        if (*pcVar2 == '\0') {
          return 1;
        }
      } while( true );
    }
    if (iVar1 == 0) {
      return 1;
    }
  }
  else {
    iVar9 = iVar7;
    printk(":%s: Type = %d Channel = %d phymode_idx = %d\n","Show_ChannelSet_Proc",iVar5,uVar6,iVar7
          );
    if (iVar5 == 0) {
      if (0 < DebugLevel) {
        printk("\n%-8s%-8s%-16s\n","Regclass","Spacing","Channelset/CenterFreq",iVar9);
      }
      goto LAB_001421f8;
    }
    if (iVar1 == 0) {
      uVar8 = 0;
      goto LAB_00142190;
    }
  }
  if (iVar7 == 1) {
    uVar8 = get_regulatory_class(param_1,uVar6 & 0xff,0x20,iVar1);
  }
  else {
    if (iVar7 == 2) {
      uVar8 = 0x1c0;
    }
    else {
      uVar8 = 0x10;
    }
    uVar8 = get_regulatory_class(param_1,uVar6 & 0xff,uVar8,iVar1);
  }
LAB_00142190:
  if (0 < DebugLevel) {
    printk("OpClass(%d) Channel(%d)\n",uVar8,uVar6);
  }
  return 1;
}

