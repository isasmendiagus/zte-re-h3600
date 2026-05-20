// module: mt7915.ko
// function: eventDispatcher @ 0x8ae90
// size: 6016 bytes
//

/* WARNING: Type propagation algorithm not settling */

void eventDispatcher(int param_1,undefined4 *param_2,uint param_3)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  
  uVar5 = *param_2;
  if (0 < DebugLevel) {
    printk("%s: u4EventId = %u, len = %u\n","eventDispatcher",uVar5,param_3);
  }
  switch(uVar5) {
  case 0:
    if (DebugLevel < 0) {
LAB_0008bffc:
      if (param_3 == 0) {
        return;
      }
    }
    else {
      printk("%s: MU_EVENT_MU_ENABLE\n","eventDispatcher");
      if (-1 < DebugLevel) {
        printk(&_LC0,"ShowMuEnableCallback");
        if ((DebugLevel < 0) ||
           (printk("MU enable:%x",*(undefined1 *)(param_2 + 1)), DebugLevel < 0)) goto LAB_0008bffc;
        printk("Resp Payload: ");
      }
      iVar3 = DebugLevel;
      if (param_3 == 0) goto LAB_0008bfd0;
    }
    uVar4 = 0;
    iVar3 = DebugLevel;
    do {
      if (-1 < iVar3) {
        printk(&_LC2,(int)*(char *)((int)param_2 + uVar4));
        iVar3 = DebugLevel;
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < param_3);
    goto LAB_0008bfd0;
  case 1:
    if (DebugLevel < 0) {
LAB_0008bfac:
      if (param_3 == 0) {
        return;
      }
    }
    else {
      printk("%s: MU_EVENT_MUPROFILE_ENTRY\n","eventDispatcher");
      if (-1 < DebugLevel) {
        printk(&_LC0,"ShowMuProfileEntryCallback");
        if (-1 < DebugLevel) {
          printk("mu table index %d\n",*(undefined1 *)(param_2 + 1));
          if (DebugLevel < 0) goto LAB_0008c2c4;
          printk("Valid  %d\n",*(undefined1 *)((int)param_2 + 5));
          if (-1 < DebugLevel) {
            printk("BAMask %x\n",*(byte *)((int)param_2 + 6) & 0xf);
            goto LAB_0008c284;
          }
        }
        goto LAB_0008bfac;
      }
LAB_0008c284:
      if (-1 < DebugLevel) {
        printk("wlanIdx %d\n",*(undefined1 *)((int)param_2 + 7));
        if (-1 < DebugLevel) {
          printk("rsp payload len %d\n",param_3);
LAB_0008c2c4:
          if (-1 < DebugLevel) {
            printk("Resp Payload: ");
            goto LAB_0008c2e8;
          }
        }
        goto LAB_0008bfac;
      }
LAB_0008c2e8:
      iVar3 = DebugLevel;
      if (param_3 == 0) goto LAB_0008bfd0;
    }
    uVar4 = 0;
    iVar3 = DebugLevel;
    do {
      if (-1 < iVar3) {
        printk(&_LC2,(int)*(char *)((int)param_2 + uVar4));
        iVar3 = DebugLevel;
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < param_3);
LAB_0008bfd0:
    if (iVar3 < 0) {
      return;
    }
    printk(&_LC3);
    goto joined_r0x0008bd3c;
  case 2:
    if (-1 < DebugLevel) {
      printk("%s: MU_EVENT_GROUP_TBL_ENTRY\n","eventDispatcher");
    }
    goto LAB_0008ab0c;
  case 3:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_CLUSTER_TBL_ENTRY\n","eventDispatcher");
    if (DebugLevel < 0) {
LAB_0008bee8:
      if (DebugLevel < 0) goto joined_r0x0008bd3c;
      printk("GID User Position [0] = %x\n",param_2[4]);
      if (DebugLevel < 0) {
        return;
      }
      printk("GID User Position [1] = %x\n",param_2[5]);
    }
    else {
      printk(&_LC0,"ShowClusterTblEntryCallback");
      if (DebugLevel < 0) {
        return;
      }
      printk("Cluster index %d\n",*(undefined1 *)(param_2 + 1));
      if (-1 < DebugLevel) {
        printk("GID User Membership Status [0] = %x\n",param_2[2]);
        if (DebugLevel < 0) {
          return;
        }
        printk("GID User Membership Status [1] = %x\n",param_2[3]);
        goto LAB_0008bee8;
      }
    }
    if (DebugLevel < 0) {
      return;
    }
    printk("GID User Position [2] = %x\n",param_2[6]);
    if (DebugLevel < 0) {
      return;
    }
    printk("GID User Position [3] = %x\n",param_2[7]);
    goto joined_r0x0008bd3c;
  case 4:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_GROUP_USER_THRESHOLD\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowGroupUserThresholdCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("Group user Threshold minimum value: %x\n",*(undefined1 *)(param_2 + 1));
    if (DebugLevel < 0) {
      return;
    }
    printk("Group user Threshold maximum value: %x\n",*(undefined1 *)((int)param_2 + 5));
    break;
  case 5:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_GROUP_NSS_THRESHOLD\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowGroupNssThresholdCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("Group Nss Threshold minimum value: %x\n",*(undefined1 *)(param_2 + 1));
    if (DebugLevel < 0) {
      return;
    }
    printk("Group Nss Threshold maximum value: %x\n",*(undefined1 *)((int)param_2 + 5));
    break;
  case 6:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_TXREQ_MIN_TIME\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowTxReqMinTimeCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("TxReqMinTime value: %x\n",*(undefined2 *)(param_2 + 1));
joined_r0x0008bd3c:
    if (DebugLevel < 0) {
      return;
    }
    goto LAB_0008b1c0;
  case 7:
    if (-1 < DebugLevel) {
      printk("%s: MU_EVENT_CALC_INIT_MCS\n","eventDispatcher");
    }
LAB_0008ab0c:
    if ((DebugLevel < 0) || (printk(&_LC0,"ShowGroupTblEntryCallback"), DebugLevel < 0)) {
      if (param_3 == 0) {
        return;
      }
    }
    else {
      printk("Resp Payload: ");
      iVar3 = DebugLevel;
      if (param_3 == 0) goto LAB_0008ab50;
    }
    uVar4 = 0;
    iVar3 = DebugLevel;
    do {
      if (-1 < iVar3) {
        printk(&_LC2,(int)*(char *)((int)param_2 + uVar4));
        iVar3 = DebugLevel;
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < param_3);
LAB_0008ab50:
    if (iVar3 < 0) {
      return;
    }
    printk(&_LC3);
    if (DebugLevel < 0) {
      return;
    }
    printk("group table index %d\n",param_2[1]);
    if (DebugLevel < 0) {
      return;
    }
    printk("Number of User  %d\n",*(byte *)(param_2 + 2) & 3);
    if (DebugLevel < 0) {
      return;
    }
    printk("BW %d\n",((uint)*(byte *)(param_2 + 2) << 0x1c) >> 0x1e);
    if (DebugLevel < 0) {
      return;
    }
    printk("NS0 %d\n",((uint)*(byte *)(param_2 + 2) << 0x1b) >> 0x1f);
    if (DebugLevel < 0) {
      return;
    }
    printk("NS1 %d\n",((uint)*(byte *)(param_2 + 2) << 0x1a) >> 0x1f);
    if (DebugLevel < 0) {
      return;
    }
    printk("NS2 %d\n",((uint)*(byte *)(param_2 + 2) << 0x19) >> 0x1f);
    if (DebugLevel < 0) {
      return;
    }
    printk("NS3 %d\n",*(byte *)(param_2 + 2) >> 7);
    if (DebugLevel < 0) {
      return;
    }
    printk("PFIDUser0  %d\n",*(undefined1 *)((int)param_2 + 9));
    if (DebugLevel < 0) {
      return;
    }
    printk("PFIDUser1  %d\n",*(undefined1 *)((int)param_2 + 10));
    if (DebugLevel < 0) {
      return;
    }
    printk("PFIDUser2  %d\n",*(undefined1 *)((int)param_2 + 0xb));
    if (DebugLevel < 0) {
      return;
    }
    printk("PFIDUser3  %d\n",*(undefined1 *)(param_2 + 3));
    if (DebugLevel < 0) {
      return;
    }
    printk("SGI  %d\n",*(undefined1 *)((int)param_2 + 0xd));
    if (DebugLevel < 0) {
      return;
    }
    printk("USED  %d\n",*(undefined1 *)((int)param_2 + 0xe));
    if (DebugLevel < 0) {
      return;
    }
    printk("DISABLED  %d\n",*(undefined1 *)((int)param_2 + 0xf));
    if (DebugLevel < 0) {
      return;
    }
    printk("initMCS0  %d\n",*(byte *)(param_2 + 4) & 0xf);
    if (DebugLevel < 0) {
      return;
    }
    printk("initMCS1  %d\n",*(byte *)(param_2 + 4) >> 4);
    if (DebugLevel < 0) {
      return;
    }
    printk("initMCS2  %d\n",*(byte *)((int)param_2 + 0x11) & 0xf);
    if (DebugLevel < 0) {
      return;
    }
    printk("initMCS3  %d\n",*(byte *)((int)param_2 + 0x11) >> 4);
    if (DebugLevel < 0) {
      return;
    }
    printk("dMCS0  %d\n",*(byte *)((int)param_2 + 0x12) & 0xf);
    if (DebugLevel < 0) {
      return;
    }
    printk("dMCS1  %d\n",*(byte *)((int)param_2 + 0x12) >> 4);
    if (DebugLevel < 0) {
      return;
    }
    printk("dMCS2  %d\n",*(byte *)((int)param_2 + 0x13) & 0xf);
    if (DebugLevel < 0) {
      return;
    }
    printk("dMCS3  %d\n",*(byte *)((int)param_2 + 0x13) >> 4);
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC26);
    return;
  case 8:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_SU_NSS_CHECK\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowSuNssCheckCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("SU NSS Check value: %x\n",*(undefined1 *)(param_2 + 1));
    break;
  case 9:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_TXOP_DEFAULT\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowTxopDefaultCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("TXOP default value: %x\n",param_2[1]);
    break;
  case 10:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_SU_LOSS_THRESHOLD\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowSuLossThresholdCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("su loss threshold value: %x\n",param_2[1]);
    break;
  case 0xb:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_MU_GAIN_THRESHOLD\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowMuGainThresholdCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("mu gain threshold value: %x\n",param_2[1]);
    break;
  case 0xc:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_SECONDARY_AC_POLICY\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowSecondaryAcPolicyCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("secondary ac policy value: %x\n",*(undefined1 *)(param_2 + 1));
    break;
  case 0xd:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_GROUP_TBL_DMCS_MASK\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowGroupTblDmcsMaskCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("group table dmcs mask value: %x\n",*(undefined1 *)(param_2 + 1));
    break;
  case 0xe:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_MAX_GROUP_SEARCH_CNT\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowMaxGroupSearchCntCallback");
    if (DebugLevel < 0) {
      return;
    }
    printk("max. group search cnt value: %x\n",param_2[1]);
    break;
  case 0xf:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_MUPROFILE_TX_STS_CNT\n","eventDispatcher");
    if (DebugLevel < 0) {
LAB_0008b810:
      if (-1 < DebugLevel) {
        printk("c(n,2) delta mcs: %x\n",*(undefined2 *)((int)param_2 + 10));
        if (DebugLevel < 0) {
          return;
        }
        printk("c(n,2) tx fail count: %x\n",*(undefined2 *)(param_2 + 3));
        goto LAB_0008b850;
      }
LAB_0008b890:
      if (-1 < DebugLevel) {
        printk("c(n,3) rate down: %x\n",*(undefined2 *)((int)param_2 + 0x12));
        if (DebugLevel < 0) {
          return;
        }
        printk("c(n,3) delta mcs: %x\n",*(undefined2 *)(param_2 + 5));
        goto LAB_0008b8d0;
      }
LAB_0008b910:
      if (-1 < DebugLevel) {
        printk("c(n,4) used: %x\n",*(undefined2 *)((int)param_2 + 0x1a));
        if (DebugLevel < 0) {
          return;
        }
        printk("c(n,4) rate down: %x\n",*(undefined2 *)(param_2 + 7));
        goto LAB_0008b950;
      }
    }
    else {
      printk(&_LC0,"ShowMuProfileTxStsCntCallback");
      if (DebugLevel < 0) {
        return;
      }
      printk("mu profile index: %x\n",*(undefined2 *)(param_2 + 1));
      if (-1 < DebugLevel) {
        printk("c(n,2) used: %x\n",*(undefined2 *)((int)param_2 + 6));
        if (DebugLevel < 0) {
          return;
        }
        printk("c(n,2) rate down: %x\n",*(undefined2 *)(param_2 + 2));
        goto LAB_0008b810;
      }
LAB_0008b850:
      if (-1 < DebugLevel) {
        printk("c(n,2) tx succes count: %x\n",*(undefined2 *)((int)param_2 + 0xe));
        if (DebugLevel < 0) {
          return;
        }
        printk("c(n,3) used: %x\n",*(undefined2 *)(param_2 + 4));
        goto LAB_0008b890;
      }
LAB_0008b8d0:
      if (-1 < DebugLevel) {
        printk("c(n,3) tx fail count: %x\n",*(undefined2 *)((int)param_2 + 0x16));
        if (DebugLevel < 0) {
          return;
        }
        printk("c(n,3) tx succes count: %x\n",*(undefined2 *)(param_2 + 6));
        goto LAB_0008b910;
      }
LAB_0008b950:
      if (DebugLevel < 0) {
        return;
      }
      printk("c(n,4) delta mcs: %x\n",*(undefined2 *)((int)param_2 + 0x1e));
      if (DebugLevel < 0) {
        return;
      }
      printk("c(n,4) tx fail count: %x\n",*(undefined2 *)(param_2 + 8));
    }
    if (DebugLevel < 0) {
      return;
    }
    printk("c(n,4) tx succes count: %x\n",*(undefined2 *)((int)param_2 + 0x22));
    break;
  case 0x10:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_STATUS\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC0,"ShowStatusOfCommand");
    goto joined_r0x0008b1a0;
  default:
    goto switchD_0008aec0_caseD_11;
  case 0x46:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
    }
    else {
      printk("%s: MU_EVENT_HQA_GET_INIT_MCS\n","eventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "hqa_wifi_test_mu_get_init_mcs_callback";
        pcVar1 = "%s: rsp_payload is null!!\n";
        goto LAB_0008b2fc;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "hqa_wifi_test_mu_get_init_mcs_callback";
        pcVar1 = "%s: msg is null!!\n";
        goto LAB_0008b2fc;
      }
    }
    puVar6 = *(undefined4 **)(param_1 + 0xc);
    if (puVar6 != (undefined4 *)0x0) {
      *puVar6 = param_2[1];
      iVar3 = DebugLevel;
      puVar6[1] = param_2[2];
      puVar6[2] = param_2[3];
      puVar6[3] = param_2[4];
      if (iVar3 < 1) {
        return;
      }
      printk("%s: EVENT_HQA_INIT_MCS\n","hqa_wifi_test_mu_get_init_mcs_callback");
      if (DebugLevel < 1) {
        return;
      }
      printk("EventId:%u InitMCS[user0~user3]:%u %u %u %u\n",*param_2,param_2[1],param_2[2],
             param_2[3],param_2[4]);
      return;
    }
    if (DebugLevel < 0) {
      return;
    }
    pcVar2 = "hqa_wifi_test_mu_get_init_mcs_callback";
    pcVar1 = "%s: Error !! buffer not specified by cmd\n";
    goto LAB_0008b2fc;
  case 0x47:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
    }
    else {
      printk("%s: MU_EVENT_HQA_GET_LQ\n","eventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "hqa_wifi_test_mu_get_lq_callback";
        pcVar1 = "%s: rsp_payload is null!!\n";
        goto LAB_0008b2fc;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "hqa_wifi_test_mu_get_lq_callback";
        pcVar1 = "%s: msg is null!!\n";
        goto LAB_0008b2fc;
      }
    }
    puVar6 = *(undefined4 **)(param_1 + 0xc);
    if (puVar6 == (undefined4 *)0x0) {
      if (DebugLevel < 0) {
        return;
      }
      pcVar2 = "hqa_wifi_test_mu_get_lq_callback";
      pcVar1 = "%s: Error !! buffer not specified by cmd\n";
      goto LAB_0008b2fc;
    }
    *puVar6 = param_2[1];
    puVar6[1] = param_2[2];
    puVar6[2] = param_2[3];
    puVar6[3] = param_2[4];
    puVar6[4] = param_2[5];
    puVar6[5] = param_2[6];
    puVar6[6] = param_2[7];
    puVar6[7] = param_2[8];
    puVar6[8] = param_2[9];
    puVar6[9] = param_2[10];
    puVar6[10] = param_2[0xb];
    puVar6[0xb] = param_2[0xc];
    puVar6[0xc] = param_2[0xd];
    puVar6[0xd] = param_2[0xe];
    puVar6[0xe] = param_2[0xf];
    puVar6[0xf] = param_2[0x10];
    puVar6[0x10] = param_2[0x11];
    iVar3 = DebugLevel;
    puVar6[0x11] = param_2[0x12];
    puVar6[0x12] = param_2[0x13];
    puVar6[0x13] = param_2[0x14];
    if (iVar3 < 1) {
      return;
    }
    printk("%s:EVENT_HQA_GET_MU_CALC_LQ\n","hqa_wifi_test_mu_get_lq_callback");
    if (DebugLevel < 1) {
LAB_0008b46c:
      if (0 < DebugLevel) {
        printk("lq_report[0][3] = 0x%x\n",param_2[4]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[0][4] = 0x%x\n",param_2[5]);
        goto LAB_0008b4ac;
      }
LAB_0008b4ec:
      if (0 < DebugLevel) {
        printk("lq_report[1][2] = 0x%x\n",param_2[8]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[1][3] = 0x%x\n",param_2[9]);
        goto LAB_0008b52c;
      }
LAB_0008b56c:
      if (0 < DebugLevel) {
        printk("lq_report[2][1] = 0x%x\n",param_2[0xc]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[2][2] = 0x%x\n",param_2[0xd]);
        goto LAB_0008b5ac;
      }
LAB_0008b5ec:
      if (0 < DebugLevel) {
        printk("lq_report[3][0] = 0x%x\n",param_2[0x10]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[3][1] = 0x%x\n",param_2[0x11]);
        goto LAB_0008b62c;
      }
    }
    else {
      printk("eventId %u\n",*param_2);
      if (DebugLevel < 1) {
        return;
      }
      printk("lq_report[0][0] = 0x%x\n",param_2[1]);
      if (0 < DebugLevel) {
        printk("lq_report[0][1] = 0x%x\n",param_2[2]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[0][2] = 0x%x\n",param_2[3]);
        goto LAB_0008b46c;
      }
LAB_0008b4ac:
      if (0 < DebugLevel) {
        printk("lq_report[1][0] = 0x%x\n",param_2[6]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[1][1] = 0x%x\n",param_2[7]);
        goto LAB_0008b4ec;
      }
LAB_0008b52c:
      if (0 < DebugLevel) {
        printk("lq_report[1][4] = 0x%x\n",param_2[10]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[2][0] = 0x%x\n",param_2[0xb]);
        goto LAB_0008b56c;
      }
LAB_0008b5ac:
      if (0 < DebugLevel) {
        printk("lq_report[2][3] = 0x%x\n",param_2[0xe]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[2][4] = 0x%x\n",param_2[0xf]);
        goto LAB_0008b5ec;
      }
LAB_0008b62c:
      if (DebugLevel < 1) {
        return;
      }
      printk("lq_report[3][2] = 0x%x\n",param_2[0x12]);
      if (DebugLevel < 1) {
        return;
      }
      printk("lq_report[3][3] = 0x%x\n",param_2[0x13]);
    }
    if (DebugLevel < 1) {
      return;
    }
    pcVar2 = (char *)param_2[0x14];
    pcVar1 = "lq_report[3][4] = 0x%x\n";
LAB_0008b2fc:
    printk(pcVar1,pcVar2);
    return;
  case 0x48:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
    }
    else {
      printk("%s: MU_EVENT_HQA_GET_SU_LQ\n","eventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "hqa_wifi_test_mu_get_su_lq_callback";
        pcVar1 = "%s: rsp_payload is null!!\n";
        goto LAB_0008b2fc;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "hqa_wifi_test_mu_get_su_lq_callback";
        pcVar1 = "%s: msg is null!!\n";
        goto LAB_0008b2fc;
      }
    }
    puVar6 = *(undefined4 **)(param_1 + 0xc);
    if (puVar6 == (undefined4 *)0x0) {
      if (DebugLevel < 0) {
        return;
      }
      pcVar2 = "hqa_wifi_test_mu_get_su_lq_callback";
      pcVar1 = "%s: Error !! buffer not specified by cmd\n";
    }
    else {
      *puVar6 = param_2[1];
      iVar3 = DebugLevel;
      puVar6[1] = param_2[2];
      puVar6[2] = param_2[3];
      puVar6[3] = param_2[4];
      puVar6[4] = param_2[5];
      if (iVar3 < 1) {
        return;
      }
      printk("%s:EVENT_HQA_GET_SU_CALC_LQ\n","hqa_wifi_test_mu_get_su_lq_callback");
      if (0 < DebugLevel) {
        printk("eventId %u\n",*param_2);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[0] = 0x%x\n",param_2[1]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[1] = 0x%x\n",param_2[2]);
        if (DebugLevel < 1) {
          return;
        }
        printk("lq_report[2] = 0x%x\n",param_2[3]);
      }
      if (DebugLevel < 1) {
        return;
      }
      printk("lq_report[3] = 0x%x\n",param_2[4]);
      if (DebugLevel < 1) {
        return;
      }
      pcVar2 = (char *)param_2[5];
      pcVar1 = "lq_report[4] = 0x%x\n";
    }
    goto LAB_0008b2fc;
  case 0x49:
    if (DebugLevel < 0) {
      if (param_2 == (undefined4 *)0x0) {
        return;
      }
      if (param_1 == 0) {
        return;
      }
    }
    else {
      printk("%s: MU_EVENT_HQA_GET_QD\n","eventDispatcher");
      if (param_2 == (undefined4 *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "hqa_wifi_test_mu_get_qd_callback";
        pcVar1 = "%s: rsp_payload is null!!\n";
        goto LAB_0008b2fc;
      }
      if (param_1 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "hqa_wifi_test_mu_get_qd_callback";
        pcVar1 = "%s: msg is null!!\n";
        goto LAB_0008b2fc;
      }
    }
    puVar6 = *(undefined4 **)(param_1 + 0xc);
    if (puVar6 != (undefined4 *)0x0) {
      *puVar6 = param_2[1];
      iVar3 = DebugLevel;
      puVar6[1] = param_2[2];
      puVar6[2] = param_2[3];
      puVar6[3] = param_2[4];
      puVar6[4] = param_2[5];
      puVar6[5] = param_2[6];
      puVar6[6] = param_2[7];
      puVar6[7] = param_2[8];
      puVar6[8] = param_2[9];
      puVar6[9] = param_2[10];
      puVar6[10] = param_2[0xb];
      puVar6[0xb] = param_2[0xc];
      puVar6[0xc] = param_2[0xd];
      puVar6[0xd] = param_2[0xe];
      if (iVar3 < 1) {
        return;
      }
      printk("%s: EVENT_HQA_MU_QD\n","hqa_wifi_test_mu_get_qd_callback");
      if (DebugLevel < 1) {
        return;
      }
      printk("eventId:%u\n",*param_2);
      if (DebugLevel < 1) {
        return;
      }
      printk("qd_report[0~6] = %u %u %u %u %u %u %u\n",*puVar6,puVar6[1],puVar6[2],puVar6[3],
             puVar6[4],puVar6[5],puVar6[6]);
      if (DebugLevel < 1) {
        return;
      }
      printk("qd_report[7~13] = %u %u %u %u %u %u %u\n",puVar6[7],puVar6[8],puVar6[9],puVar6[10],
             puVar6[0xb],puVar6[0xc],puVar6[0xd]);
      return;
    }
    if (DebugLevel < 0) {
      return;
    }
    pcVar2 = "hqa_wifi_test_mu_get_qd_callback";
    pcVar1 = "%s: Error !! buffer not specified by cmd\n";
    goto LAB_0008b2fc;
  case 0x4a:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: MU_EVENT_HQA_STATUS\n","eventDispatcher");
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC88,"ShowStatusOfHqaCommand");
joined_r0x0008b1a0:
    if (DebugLevel < 0) {
      return;
    }
    printk("status: %x\n",*(undefined2 *)(param_2 + 1));
  }
  if (DebugLevel < 0) {
switchD_0008aec0_caseD_11:
    return;
  }
LAB_0008b1c0:
  printk(&_LC26);
  return;
}

