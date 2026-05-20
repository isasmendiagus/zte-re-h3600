// module: mt7915.ko
// function: Show_Repeater_Cli_Proc @ 0x82b88
// size: 1276 bytes
//

undefined4 Show_Repeater_Cli_Proc(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    iVar1 = wlan_operate_get_addht(iVar1);
    if (*(char *)((int)param_1 + 0x36790d) != '\0') {
      if ((((2 < DebugLevel) && (printk(&_LC66), 2 < DebugLevel)) &&
          (printk("HT Operating Mode : %d\n",*(byte *)(iVar1 + 2) & 3), 2 < DebugLevel)) &&
         (printk(&_LC66), 2 < DebugLevel)) {
        printk("\n%-19s%-4s%-4s%-4s%-4s%-8s%-7s%-7s%-7s%-7s%-10s%-6s%-6s%-6s%-6s%-7s%-7s\n",&_LC69,
               &_LC70,&_LC71,&_LC72,&_LC73,"MIMOPS","RSSI0","RSSI1","RSSI2","RSSI3",&_LC79,&_LC80,
               &_LC81,&_LC82,&_LC83,&_LC84,&_LC85);
      }
      piVar4 = param_1 + 0x28748;
      for (iVar1 = 0; iVar2 = HcGetMaxStaNum(param_1), iVar1 < iVar2; iVar1 = iVar1 + 1) {
        if ((((piVar4 != (int *)0x0) && (*piVar4 == 2 || *piVar4 == 0x40001)) &&
            ((piVar4[0x3f] == 2 &&
             ((piVar4[0x2bf] != 0 && (*(char *)(piVar4[0x2bf] + 5) == '\x02')))))) &&
           (getRate((short)piVar4[0x2f]), 2 < DebugLevel)) {
          iVar2 = piVar4[0x2bf];
          uVar7 = (uint)*(byte *)(iVar2 + 0x86);
          uVar8 = (uint)*(byte *)(iVar2 + 0x87);
          uVar6 = (uint)*(byte *)(iVar2 + 0x88);
          printk("%02x:%02x:%02x:%02x:%02x:%02x  ",*(undefined1 *)(iVar2 + 0x83),
                 *(undefined1 *)(iVar2 + 0x84),*(undefined1 *)(iVar2 + 0x85),uVar7,uVar8,uVar6);
          if (DebugLevel < 3) {
LAB_00082d28:
            if (DebugLevel < 3) {
LAB_00082da4:
              if (DebugLevel < 3) {
LAB_00082e5c:
                if (DebugLevel < 3) {
LAB_00082ef0:
                  if (2 < DebugLevel) {
                    iVar2 = piVar4[0x2dd];
                    iVar5 = piVar4[0x2dc];
                    if (iVar2 == 0) {
                      uVar3 = 0;
                    }
                    else {
                      uVar3 = __aeabi_uidiv((iVar2 - iVar5) * 100,iVar2);
                    }
                    printk("%-10d, %d, %d%%\n",iVar5,iVar2,uVar3);
                    if (2 < DebugLevel) {
                      printk(&_LC66);
                    }
                  }
                }
                else {
                  printk(&_LC26,((uint)*(byte *)((int)param_1 + iVar1 * 0x14c0 + 0xa1ddd) << 0x1e)
                                >> 0x1f);
                  if (2 < DebugLevel) {
                    printk(&_LC26,((uint)*(byte *)((int)param_1 + iVar1 * 0x14c0 + 0xa1ddd) << 0x1d)
                                  >> 0x1f);
LAB_00082eb0:
                    if ((2 < DebugLevel) &&
                       (printk(&_LC87,piVar4[0x2c2] - piVar4[0x2ba]), 2 < DebugLevel)) {
                      printk(&_LC87,0);
                      goto LAB_00082ef0;
                    }
                  }
                }
              }
              else {
                printk(&_LC87,(int)*(char *)((int)piVar4 + 0x10f));
                if (2 < DebugLevel) {
                  uVar3 = get_phymode_str(*(byte *)((int)param_1 + iVar1 * 0x14c0 + 0xa1ddd) >> 5);
                  printk("%-10s",uVar3);
LAB_00082e00:
                  if (DebugLevel < 3) goto LAB_00082eb0;
                  uVar3 = get_bw_str(((uint)*(ushort *)(param_1 + iVar1 * 0x530 + 0x28777) << 0x17)
                                     >> 0x1e);
                  printk(&_LC89,uVar3);
                  if (2 < DebugLevel) {
                    printk(&_LC26,*(byte *)(param_1 + iVar1 * 0x530 + 0x28777) & 0x3f);
                    goto LAB_00082e5c;
                  }
                }
              }
            }
            else {
              printk(&_LC25,(char)piVar4[0x344]);
              if (2 < DebugLevel) {
                printk(&_LC87,(int)(char)piVar4[0x43]);
LAB_00082d64:
                if (DebugLevel < 3) goto LAB_00082e00;
                printk(&_LC87,(int)*(char *)((int)piVar4 + 0x10d));
                if (2 < DebugLevel) {
                  printk(&_LC87,(int)*(char *)((int)piVar4 + 0x10e));
                  goto LAB_00082da4;
                }
              }
            }
          }
          else {
            printk(&_LC24,(short)piVar4[0x3e]);
            if (2 < DebugLevel) {
              printk("%-4d-%d",*(undefined1 *)((int)piVar4 + 0xe5),(char)piVar4[0x39],DebugLevel,
                     uVar7,uVar8,uVar6);
              if (DebugLevel < 3) goto LAB_00082d64;
              printk(&_LC24,(char)piVar4[0x2be]);
              if (2 < DebugLevel) {
                printk(&_LC24,piVar4[0x2d] & 1);
                goto LAB_00082d28;
              }
            }
          }
        }
        piVar4 = piVar4 + 0x530;
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

