// module: mt7915.ko
// function: MuraEventDispatcher @ 0x93ed8
// size: 3988 bytes
//

void MuraEventDispatcher(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  int extraout_r1;
  int iVar4;
  int extraout_r1_00;
  int extraout_r1_01;
  int extraout_r1_02;
  int extraout_r1_03;
  int extraout_r1_04;
  int extraout_r1_05;
  int extraout_r1_06;
  int extraout_r1_07;
  int extraout_r1_08;
  int extraout_r1_09;
  int extraout_r1_10;
  int extraout_r1_11;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  bool bVar12;
  ushort local_30;
  
  uVar6 = *param_2;
  if (DebugLevel < 0) {
    switch(uVar6) {
    case 0:
      iVar7 = DebugLevel;
LAB_000941cc:
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
LAB_000941d4:
      if (((-1 < DebugLevel) &&
          (printk("\n Number of Waiting MUser : %2d\n",*(undefined1 *)((int)param_2 + 0xe)),
          iVar7 = extraout_r1_02, -1 < DebugLevel)) &&
         (printk("\n Number of SU Current Space : %2d\n",*(undefined1 *)((int)param_2 + 0xf)),
         iVar7 = extraout_r1_03, -1 < DebugLevel)) {
        printk("\n MU-RGA Sounding Candidate WLAN ID List :\n");
        iVar7 = extraout_r1_04;
      }
      break;
    case 1:
switchD_00093f00_caseD_1:
      if (DebugLevel < 0) {
        return;
      }
      printk("%s: MURA_EVENT_GET_ALGORITHM_GROUP_STATE\n","MuraEventDispatcher");
      if (param_2 != (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        printk("\n MU-RGA Group Entry Information :");
        if (DebugLevel < 0) {
          return;
        }
        printk("\n GPID MNUM\n");
        if (DebugLevel < 0) {
          return;
        }
        printk(" %4d %4d\n",*(ushort *)(param_2 + 7) >> 5,*(byte *)((int)param_2 + 0x19) >> 6);
        if (DebugLevel < 0) {
          if ((*(byte *)((int)param_2 + 0x1e) & 1) != 0) {
            return;
          }
        }
        else {
          printk(" MU0_ID MU1_ID MU2_ID MU3_ID\n");
          if (DebugLevel < 0) {
            return;
          }
          printk(" %6d %6d %6d %6d\n",*(byte *)((int)param_2 + 0x1a) & 0x1f,
                 ((uint)*(ushort *)((int)param_2 + 0x1a) << 0x16) >> 0x1b,
                 ((uint)*(byte *)((int)param_2 + 0x1b) << 0x19) >> 0x1b,
                 *(byte *)(param_2 + 7) & 0x1f);
          if (DebugLevel < 0) {
            return;
          }
          printk(" RATE0 RATE1 RATE2 RATE3\n");
          if (DebugLevel < 0) {
            return;
          }
          uVar5 = (uint)*(byte *)((int)param_2 + 0x19);
          printk(" %5d %5d %5d %5d\n",(*(byte *)(param_2 + 4) & 0xf) + (uVar5 & 1) * 10,
                 ((int)(uVar5 << 0x1e) >> 0x1f) * -10 + (uint)(*(byte *)(param_2 + 4) >> 4),
                 (*(byte *)((int)param_2 + 0x11) & 0xf) + ((int)(uVar5 << 0x1d) >> 0x1f) * -10,
                 ((int)(uVar5 << 0x1c) >> 0x1f) * -10 + (uint)(*(byte *)((int)param_2 + 0x11) >> 4))
          ;
          if ((*(byte *)((int)param_2 + 0x1e) & 1) != 0) {
            if (DebugLevel < 0) {
              return;
            }
            pcVar1 = "\n";
            goto LAB_0009492c;
          }
        }
        if (DebugLevel < 0) {
          return;
        }
        pcVar1 = "\n No Valid Group Entry\n\n";
LAB_0009492c:
        printk(pcVar1);
        return;
      }
      if (DebugLevel < 0) {
        return;
      }
      pcVar3 = "mura_algorithm_group_state_callback";
      pcVar1 = "%s: error !! rsp_payload is null!!\n";
      goto LAB_00094550;
    case 2:
switchD_00093f00_caseD_2:
      if (DebugLevel < 0) {
        if (param_2 == (undefined4 *)0x0) {
          return;
        }
LAB_00094198:
        iVar7 = 0;
        puVar8 = param_2;
        do {
          if (-1 < DebugLevel) {
            local_30 = (ushort)*(byte *)(puVar8 + 0x15);
            printk(" %3d %4d %7d %7d %4d %7d %7d %7d %7d %7d\n",iVar7,*(undefined1 *)(puVar8 + 1),
                   *(undefined1 *)(puVar8 + 6),*(undefined1 *)(puVar8 + 0xb),
                   *(undefined1 *)((int)puVar8 + 0xe),*(undefined1 *)((int)puVar8 + 0x22),
                   *(undefined1 *)((int)puVar8 + 0x36),
                   (int)(short)(ushort)*(byte *)(puVar8 + 0x10) *
                   (int)(short)(ushort)*(byte *)((int)param_2 + 0x5e),
                   (int)(short)(ushort)*(byte *)((int)puVar8 + 0x4a) *
                   (int)(short)(ushort)*(byte *)((int)param_2 + 0x5f),
                   (int)(short)local_30 * (int)(short)(ushort)*(byte *)(param_2 + 0x18));
          }
          iVar7 = iVar7 + 1;
          puVar8 = (undefined4 *)((int)puVar8 + 1);
        } while (iVar7 != 10);
        return;
      }
      printk("%s: MURA_EVENT_GET_ALGORITHM_HWFB_STATE\n","MuraEventDispatcher");
      if (param_2 != (undefined4 *)0x0) {
        if ((-1 < DebugLevel) &&
           (printk("\n MU-RGA Hardware fallback Information :"), -1 < DebugLevel)) {
          printk("\n MCS DnEn DnThres DnValue UpEn UpThres UpValue 20BSamp 40BSamp 80BSamp\n");
        }
        goto LAB_00094198;
      }
      if (DebugLevel < 0) {
        return;
      }
      pcVar3 = "mura_algorithm_hwfb_state_callback";
      pcVar1 = "%s: error !! rsp_payload is null!!\n";
      goto LAB_00094550;
    case 3:
switchD_00093f00_caseD_3:
      if (DebugLevel < 0) {
        return;
      }
      printk("%s: MURA_EVENT_PFID_STAT\n","MuraEventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "mura_algorithm_pfid_stat_callback";
        pcVar1 = "%s: Event is NULL!!\n";
      }
      else {
        if (DebugLevel < 1) {
          return;
        }
        printk("Value of PFID stat are :-\n");
        if (DebugLevel < 1) {
          return;
        }
        printk("WlanIdx = %d\n",*(undefined1 *)((int)param_2 + 0xd));
        if (DebugLevel < 1) {
          return;
        }
        printk("Mobility = %d\n",*(undefined1 *)(param_2 + 1));
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn2 SuccCnt = %u\n",param_2[4]);
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn2 FailCnt = %u\n",param_2[5]);
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn3 SuccCnt = %u\n",param_2[6]);
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn3 FailCnt = %u\n",param_2[7]);
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn4 SuccCnt = %u\n",param_2[8]);
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn4 FailCnt = %u\n",param_2[9]);
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn2 TxPER = %u\n",*(undefined1 *)(param_2 + 10));
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn3 TxPER = %u\n",*(undefined1 *)((int)param_2 + 0x29));
        if (DebugLevel < 1) {
          return;
        }
        printk("Cn4 TxPER = %u\n",*(undefined1 *)((int)param_2 + 0x2a));
        if (DebugLevel < 1) {
          return;
        }
        printk("Sounding Period = %u\n",*(undefined1 *)((int)param_2 + 9));
        if (DebugLevel < 1) {
          return;
        }
        printk("Min Sounding Period = %u\n",*(undefined1 *)((int)param_2 + 10));
        if (DebugLevel < 1) {
          return;
        }
        printk("Max Sounding Period = %u\n",*(undefined1 *)((int)param_2 + 0xb));
        if (DebugLevel < 1) {
          return;
        }
        printk("Sounding Period Step = %u\n",*(undefined1 *)(param_2 + 3));
        if (DebugLevel < 1) {
          return;
        }
        printk("Succ Sounding = %u\n",*(undefined2 *)(param_2 + 0xb));
        if (DebugLevel < 1) {
          return;
        }
        printk("Fail Sounding = %u\n",*(undefined2 *)((int)param_2 + 0x2e));
        if (DebugLevel < 1) {
          return;
        }
        pcVar3 = (char *)(uint)*(byte *)(param_2 + 0xc);
        pcVar1 = "Sounding Fail Rate = %u\n";
      }
      goto LAB_00094550;
    default:
      goto switchD_00093f00_default;
    }
  }
  else {
    printk("%s: u4EventId = %u, len = %u\n","MuraEventDispatcher",uVar6,param_3);
    switch(uVar6) {
    case 0:
      iVar7 = extraout_r1_05;
      if (DebugLevel < 0) goto LAB_000941cc;
      printk("%s: MURA_EVENT_GET_ALGORITHM_STATE\n","MuraEventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar3 = "mura_algorithm_state_callback";
        pcVar1 = "%s: error !! rsp_payload is null!!\n";
        goto LAB_00094550;
      }
      iVar7 = extraout_r1_06;
      if ((-1 < DebugLevel) &&
         (printk(&_LC3,*(undefined1 *)(param_2 + 3)), iVar7 = extraout_r1_07, -1 < DebugLevel)) {
        printk("\n Number of Sounding MUser : %2d\n",*(undefined1 *)((int)param_2 + 0xd));
        iVar7 = extraout_r1_08;
        goto LAB_000941d4;
      }
      break;
    case 1:
      goto switchD_00093f00_caseD_1;
    case 2:
      goto switchD_00093f00_caseD_2;
    case 3:
      goto switchD_00093f00_caseD_3;
    default:
      goto switchD_00093f00_default;
    }
  }
  iVar2 = DebugLevel;
  puVar8 = param_2 + 0x3c;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined1 *)puVar8);
      iVar2 = DebugLevel;
      iVar7 = extraout_r1_11;
    }
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  } while (puVar8 != param_2 + 0x3e);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, iVar7 = extraout_r1_09, -1 < DebugLevel))
  {
    printk("\n MU-RGA Group Entry Candidate List :");
    iVar2 = DebugLevel;
    iVar7 = extraout_r1_10;
  }
  puVar10 = (undefined1 *)((int)param_2 + 0x13f);
  pcVar1 = (char *)((int)param_2 + 0xf7);
  do {
    pcVar1 = pcVar1 + 1;
    if (*pcVar1 != '\x1f') {
      puVar11 = puVar10 + -0x3f;
      uVar5 = 0;
      do {
        if ((uVar5 & 0xff) % 0x14 == 0) {
          if (-1 < iVar2) {
            printk("\n %2d: ",uVar5,(uVar5 & 0xff) * -0x33333333);
            iVar2 = DebugLevel;
            goto LAB_00094280;
          }
        }
        else {
LAB_00094280:
          if (-1 < iVar2) {
            printk("%1d, ",*puVar11);
            iVar2 = DebugLevel;
          }
        }
        uVar5 = uVar5 + 1;
        puVar11 = puVar11 + 1;
      } while (uVar5 != 0x1c);
      puVar11 = puVar10 + -0x23;
      iVar7 = 0;
      do {
        iVar4 = iVar7 + 0x1c;
        bVar12 = iVar7 == (iVar7 / 0x14) * 0x14;
        iVar7 = iVar7 + 1;
        if (bVar12) {
          if (-1 < iVar2) {
            printk("\n %2d: ",iVar4);
            iVar2 = DebugLevel;
            goto LAB_0009459c;
          }
        }
        else {
LAB_0009459c:
          if (-1 < iVar2) {
            printk(&_LC13,*puVar11);
            iVar2 = DebugLevel;
          }
        }
        puVar11 = puVar11 + 1;
      } while (iVar7 != 0x23);
      iVar4 = 0;
      puVar11 = puVar10;
      do {
        iVar7 = iVar4 + 0x3f;
        bVar12 = iVar4 == (iVar4 / 0x14) * 0x14;
        iVar4 = iVar4 + 1;
        if (bVar12) {
          if (-1 < iVar2) {
            printk("\n %2d: ",iVar7);
            iVar2 = DebugLevel;
            iVar7 = extraout_r1_00;
            goto LAB_000945cc;
          }
        }
        else {
LAB_000945cc:
          if (-1 < iVar2) {
            printk(&_LC14,*puVar11);
            iVar2 = DebugLevel;
            iVar7 = extraout_r1_01;
          }
        }
        puVar11 = puVar11 + 1;
      } while (iVar4 != 5);
      if (-1 < iVar2) {
        printk(&_LC9,iVar7);
        iVar2 = DebugLevel;
        iVar7 = extraout_r1;
      }
    }
    puVar10 = puVar10 + 0x44;
  } while (puVar10 != (undefined1 *)((int)param_2 + 0x35f));
  if (-1 < iVar2) {
    printk("\n MU-RGA Cn2 Tx Succ Counter :\n",iVar7);
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 6;
  puVar9 = param_2 + 0xe;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = puVar8 + 1;
  } while (puVar8 != puVar9);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Cn2 Tx Fail Counter :\n");
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 0x16;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*puVar9);
      iVar2 = DebugLevel;
    }
    puVar9 = puVar9 + 1;
  } while (puVar9 != puVar8);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Cn3 Tx Succ Counter :\n");
    iVar2 = DebugLevel;
  }
  puVar9 = param_2 + 0x1e;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = puVar8 + 1;
  } while (puVar8 != puVar9);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Cn3 Tx Fail Counter :\n");
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 0x26;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*puVar9);
      iVar2 = DebugLevel;
    }
    puVar9 = puVar9 + 1;
  } while (puVar9 != puVar8);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Cn4 Tx Succ Counter :\n");
    iVar2 = DebugLevel;
  }
  puVar9 = param_2 + 0x2e;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = puVar8 + 1;
  } while (puVar8 != puVar9);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Cn4 Tx Fail Counter :\n");
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 0x36;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*puVar9);
      iVar2 = DebugLevel;
    }
    puVar9 = puVar9 + 1;
  } while (puVar9 != puVar8);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Cn2 Total Tx PER :\n");
    iVar2 = DebugLevel;
  }
  puVar9 = param_2 + 0x38;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined1 *)puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  } while (puVar8 != puVar9);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Cn3 Total Tx PER :\n");
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 0x3a;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined1 *)puVar9);
      iVar2 = DebugLevel;
    }
    puVar9 = (undefined4 *)((int)puVar9 + 1);
  } while (puVar9 != puVar8);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Cn4 Total Tx PER :\n");
    iVar2 = DebugLevel;
  }
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined1 *)puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  } while (puVar8 != param_2 + 0x3c);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Mobility :\n");
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 1;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined1 *)puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  } while (puVar8 != param_2 + 3);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA Delta MCS Rate :\n");
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 200;
  puVar9 = param_2 + 0xca;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined1 *)puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  } while (puVar8 != puVar9);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA MU Succ Sounding Counter :\n");
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 0xce;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined2 *)puVar9);
      iVar2 = DebugLevel;
    }
    puVar9 = (undefined4 *)((int)puVar9 + 2);
  } while (puVar9 != puVar8);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA MU Fail Sounding Counter :\n");
    iVar2 = DebugLevel;
  }
  puVar9 = param_2 + 0xd2;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined2 *)puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = (undefined4 *)((int)puVar8 + 2);
  } while (puVar8 != puVar9);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA MU Sounding Fail Rate :\n");
    iVar2 = DebugLevel;
  }
  puVar8 = param_2 + 0xd4;
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*(undefined1 *)puVar9);
      iVar2 = DebugLevel;
    }
    puVar9 = (undefined4 *)((int)puVar9 + 1);
  } while (puVar9 != puVar8);
  if ((-1 < iVar2) && (printk(&_LC9), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("\n MU-RGA DMCS Intr Count:\n");
    iVar2 = DebugLevel;
  }
  do {
    if (-1 < iVar2) {
      printk(" %2d,",*puVar8);
      iVar2 = DebugLevel;
    }
    puVar8 = puVar8 + 1;
  } while (puVar8 != param_2 + 0xdc);
  if (((iVar2 < 0) || (printk(&_LC30), DebugLevel < 0)) ||
     (printk(" Sounding Period : %d ms\n",param_2[0xdc] - param_2[0xdd]), DebugLevel < 0)) {
switchD_00093f00_default:
    return;
  }
  pcVar1 = " Group Period : %d ms\n";
  pcVar3 = (char *)(param_2[0xde] - param_2[0xdf]);
LAB_00094550:
  printk(pcVar1,pcVar3);
  return;
}

