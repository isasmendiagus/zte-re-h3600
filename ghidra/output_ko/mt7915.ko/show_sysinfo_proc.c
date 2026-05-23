// module: mt7915.ko
// function: show_sysinfo_proc @ 0xe1b0c
// size: 1848 bytes
//

undefined4 show_sysinfo_proc(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  byte *pbVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined *puVar7;
  int iVar8;
  undefined1 *puVar9;
  int *piVar10;
  int iVar11;
  char *pcVar12;
  int iVar13;
  uint uVar14;
  
  iVar13 = *param_1;
  if (*(int *)(iVar13 + 0x38) == 0x400) {
    get_scan_tab_by_wdev(param_1,param_1 + *(int *)(iVar13 + 0x3c) * 0x84dec + 0xdb6d6);
  }
  if (0 < DebugLevel) {
    printk("Device Instance\n");
  }
  piVar5 = param_1 + 3;
  iVar11 = 0;
  iVar1 = DebugLevel;
  do {
    if (iVar1 < 1) {
      piVar10 = (int *)*piVar5;
      if (piVar10 != (int *)0x0) {
LAB_000e1b60:
        iVar1 = wmode_2_str((short)piVar10[6]);
        if (iVar1 != 0) {
          if (0 < DebugLevel) {
            printk("\t\tPhyMode:%s\n",iVar1);
          }
          os_free_mem(iVar1);
        }
        uVar2 = wlan_config_get_ext_cha(piVar10);
        if ((DebugLevel < 1) ||
           (printk("\t\tChannel:%d,ExtCha:%d\n",*(undefined1 *)((int)piVar10 + 0x1a),uVar2),
           DebugLevel < 1)) {
LAB_000e1b9c:
          iVar3 = *piVar10;
          iVar1 = DebugLevel;
          if (iVar3 == 0) goto LAB_000e1bd0;
        }
        else {
          puVar7 = &_LC461;
          if ((char)piVar10[0x222] != '\x01') {
            puVar7 = &_LC501;
          }
          printk("\t\tPortSecured/ForbidTx: %d(%sSecured)/%lx\n",(char)piVar10[0x222],puVar7,
                 piVar10[0x223]);
          if (((DebugLevel < 1) ||
              (printk("\t\tEdcaIdx:%d\n",*(undefined1 *)((int)piVar10 + 0x8d7)), DebugLevel < 1)) ||
             (printk("\t\tif_dev:0x%p\tfunc_dev:[%d]0x%p\tsys_handle:0x%p\n",*piVar10,
                     *(undefined1 *)((int)piVar10 + 0xe),piVar10[1],piVar10[2]), DebugLevel < 1))
          goto LAB_000e1b9c;
          printk("\t\tIgmpSnoopEnable:%d\n",(char)piVar10[0x224]);
          iVar3 = *piVar10;
          iVar1 = DebugLevel;
          if (iVar3 == 0) goto LAB_000e1bd0;
          puVar9 = *(undefined1 **)(iVar3 + 0x1dc);
          if (0 < DebugLevel) {
            uVar2 = RtmpOsGetNetDevName();
            uVar6 = RtmpOsGetNetIfIndex(*piVar10);
            printk("\t\tOS NetDev status(%s[%d]-%02x:%02x:%02x:%02x:%02x:%02x):\n",uVar2,uVar6,
                   *puVar9,puVar9[1],puVar9[2],puVar9[3],puVar9[4],puVar9[5]);
            iVar3 = *piVar10;
            if (0 < DebugLevel) {
              uVar2 = RtmpOSGetNetDevState(iVar3);
              printk("\t\t\tdev->state: 0x%lx\n",uVar2);
              iVar3 = *piVar10;
              if (0 < DebugLevel) {
                uVar2 = RtmpOSGetNetDevFlag(iVar3);
                printk("\t\t\tdev->flag: 0x%x\n",uVar2);
                iVar3 = *piVar10;
              }
            }
          }
        }
        iVar3 = RtmpOSGetNetDevQNum(iVar3);
        iVar1 = DebugLevel;
        if (iVar3 != 0) {
          iVar8 = 0;
          do {
            if (0 < iVar1) {
              uVar2 = RtmpOSGetNetDevQState(*piVar10,iVar8);
              printk("\t\t\tdev->queue[%d].state: 0x%lx\n",iVar8,uVar2);
              iVar1 = DebugLevel;
            }
            iVar8 = iVar8 + 1;
          } while (iVar8 != iVar3);
        }
      }
    }
    else {
      printk("\tWDEV %02d:",iVar11);
      piVar10 = (int *)*piVar5;
      if (piVar10 != (int *)0x0) {
        if (0 < DebugLevel) {
          uVar2 = wdev_type2str(piVar10[5]);
          printk("\n\t\tName/Type:%s/%s\n",*piVar10,uVar2);
          if (((0 < DebugLevel) &&
              (printk("\t\tWdev(list) Idx:%d\n",(char)piVar10[3]), 0 < DebugLevel)) &&
             (printk("\t\tMacAddr:%02x:%02x:%02x:%02x:%02x:%02x\n",
                     *(undefined1 *)((int)piVar10 + 0x1b),(char)piVar10[7],
                     *(undefined1 *)((int)piVar10 + 0x1d),*(undefined1 *)((int)piVar10 + 0x1e),
                     *(undefined1 *)((int)piVar10 + 0x1f),(char)piVar10[8]), 0 < DebugLevel)) {
            printk("\t\tBSSID:%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)((int)piVar10 + 0x21),
                   *(undefined1 *)((int)piVar10 + 0x22),*(undefined1 *)((int)piVar10 + 0x23),
                   (char)piVar10[9],*(undefined1 *)((int)piVar10 + 0x25),
                   *(undefined1 *)((int)piVar10 + 0x26));
          }
        }
        goto LAB_000e1b60;
      }
      iVar1 = DebugLevel;
      if (0 < DebugLevel) {
        printk(&_LC22);
        iVar1 = DebugLevel;
      }
    }
LAB_000e1bd0:
    iVar11 = iVar11 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar11 != 0x68);
  if (((((0 < iVar1) && (printk("Memory Statistics:\n"), 0 < DebugLevel)) &&
       (printk("\tsize>\n"), 0 < DebugLevel)) &&
      ((printk("\t\tpAd = \t\t%zu bytes\n\n",0xa86c60), 0 < DebugLevel &&
       (printk("\t\t\tCommonCfg = \t%zu bytes\n",0xef0), 0 < DebugLevel)))) &&
     ((printk("\t\t\tApCfg = \t%zu bytes\n",0xb6868), 0 < DebugLevel &&
      (printk("\t\t\t\tMBSSID = \t%zu B (PerMBSS =%zu B, Total MBSS Num= %d)\n",0xb0680,0x5834,0x20)
      , 0 < DebugLevel)))) {
    printk("\t\t\t\t\tAPCLI = \t%zu bytes (PerAPCLI =%zu bytes, Total APCLI Num= %d)\n",
           &DAT_00426f60,0x2137b0,2);
  }
  pbVar4 = (byte *)hc_get_hif_ctrl(param_1[0x29e5e8]);
  if (*pbVar4 == 0) {
    iVar11 = 0xb7758;
    iVar1 = 0;
  }
  else {
    iVar1 = 0;
    piVar5 = *(int **)(pbVar4 + 8);
    do {
      piVar10 = piVar5 + 1;
      iVar1 = iVar1 + *(int *)(*piVar5 + 0x48) + *(int *)(*piVar5 + 0x3c);
      piVar5 = piVar10;
    } while (piVar10 != *(int **)(pbVar4 + 8) + *pbVar4);
    iVar11 = iVar1 + 0xb7758;
  }
  if (DebugLevel < 1) {
    uVar14 = (uint)pbVar4[1];
    if (uVar14 != 0) {
LAB_000e1c60:
      iVar1 = 0;
      piVar5 = *(int **)(pbVar4 + 4);
      do {
        piVar10 = piVar5 + 1;
        iVar3 = *piVar5;
        iVar1 = iVar1 + *(int *)(iVar3 + 0x58);
        if (*(ushort *)(iVar3 + 0x14) != 0) {
          iVar8 = *(int *)(iVar3 + 0x18);
          iVar3 = iVar8 + (uint)*(ushort *)(iVar3 + 0x14) * 0x24;
          do {
            piVar5 = (int *)(iVar8 + 0x18);
            iVar8 = iVar8 + 0x24;
            iVar1 = iVar1 + *piVar5;
          } while (iVar8 != iVar3);
        }
        piVar5 = piVar10;
      } while (piVar10 != *(int **)(pbVar4 + 4) + uVar14);
      goto LAB_000e1cac;
    }
    iVar1 = 0;
LAB_000e1cb4:
    iVar1 = iVar1 + iVar11;
    if (*(int *)(iVar13 + 0x38) == 0x400) {
LAB_000e1dd4:
      pcVar12 = "sae_parse_password_identifier" + iVar1 + 4;
    }
    else {
LAB_000e1cc4:
      pcVar12 = (char *)(iVar1 + 0x93750);
    }
    if (DebugLevel < 1) {
LAB_000e1cd4:
      iVar11 = *(int *)(iVar13 + 0x38);
      goto LAB_000e1cd8;
    }
    printk("\t\t\tMacTab = \t%zu bytes\n",0x1e4038);
    if (0 < DebugLevel) {
      printk("\t\t\tBA Control = \t%zu bytes\n",0x2f4e0);
      if (DebugLevel < 1) goto LAB_000e1cd4;
      printk("\t\t\tCounter** = \t%d bytes\n",0x3a0);
      if (*(int *)(iVar13 + 0x38) == 0x400) {
        if (0 < DebugLevel) {
          printk("\t\t\tScanTab = \t%zu bytes\n",4);
        }
        goto LAB_000e1d38;
      }
LAB_000e2224:
      pcVar12 = pcVar12 + 0x2138b8;
      goto LAB_000e1d44;
    }
    if (*(int *)(iVar13 + 0x38) != 0x400) goto LAB_000e2224;
  }
  else {
    printk("\t\t\tTxRing = \t%d bytes\n",iVar1);
    uVar14 = (uint)pbVar4[1];
    if (uVar14 != 0) goto LAB_000e1c60;
    iVar1 = 0;
LAB_000e1cac:
    if (DebugLevel < 1) goto LAB_000e1cb4;
    printk("\t\t\tRxRing = \t%d bytes\n",iVar1);
    iVar1 = iVar1 + iVar11;
    if (0 < DebugLevel) {
      printk("\t\t\tMlme = \t%zu bytes\n",0x93750);
      if (*(int *)(iVar13 + 0x38) == 0x400) {
        if (0 < DebugLevel) {
          printk("\t\t\tMlmeAux = \t%zu bytes\n",0x20e2dc);
        }
        goto LAB_000e1dd4;
      }
      goto LAB_000e1cc4;
    }
    iVar11 = *(int *)(iVar13 + 0x38);
    pcVar12 = (char *)(iVar1 + 0x93750);
    if (iVar11 == 0x400) goto LAB_000e1dd4;
LAB_000e1cd8:
    if (iVar11 != 0x400) {
      return 1;
    }
  }
LAB_000e1d38:
  pcVar12 = pcVar12 + 0x2138bc;
LAB_000e1d44:
  if (0 < DebugLevel) {
    printk("\tsize> Total = \t\t%d bytes, Others = %zu bytes\n\n",pcVar12,0xa86c60 - (int)pcVar12);
  }
  return 1;
}

