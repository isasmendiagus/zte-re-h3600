// module: mt7915.ko
// function: MT_ATERFTestCB @ 0x28a038
// size: 1860 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

int MT_ATERFTestCB(int param_1,int *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  size_t sVar7;
  uint uVar8;
  uint uVar9;
  int *piVar10;
  int *piVar11;
  bool bVar12;
  void *local_40;
  int local_3c;
  int local_38;
  int local_34;
  int iStack_30;
  undefined1 uStack_2c;
  
  if (2 < DebugLevel) {
    printk(&_LC278,"MT_ATERFTestCB",param_3,*(undefined4 *)(param_1 + 0xa3ac14));
  }
  if (param_3 == 8) goto LAB_0028a25c;
  if (("RTMPSetSTAPassPhrase"[param_1 + 3] == '\0') &&
     ((*(uint *)(param_1 + 0xa3ac14) & 0x200) == 0)) {
    return 0;
  }
  DAT_005f6a34 = *param_2;
  if (DebugLevel < 3) {
    switch(DAT_005f6a34) {
    case 1:
      goto switchD_0028a0a8_caseD_1;
    default:
      goto switchD_0028a0a8_caseD_2;
    case 10:
      goto switchD_0028a0a8_caseD_a;
    case 0xc:
switchD_0028a0a8_caseD_c:
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7615) {
        return 0;
      }
      ExtEventICapUnSolicitStatusHandler(param_1,param_2,param_3);
      return 0;
    case 0x11:
switchD_0028a0a8_caseD_11:
      RTEnqueueInternalCmd(param_1,0x16,param_2,param_3);
      goto switchD_0028a0a8_caseD_2;
    }
  }
  printk(&_LC279,"MT_ATERFTestCB");
  if (DAT_005f6a34 == 10) {
switchD_0028a0a8_caseD_a:
    if ((*(uint *)(param_1 + 0xa39ffc) & 4) != 0) {
      piVar10 = param_2 + 5;
      uVar1 = param_2[1] - 0xcU >> 3;
      if ((*(uint *)(param_1 + 0xa39ffc) & 0x80) != 0) {
        uVar8 = param_2[1] - 0xcU >> 2;
        iVar4 = DebugLevel;
        if (uVar8 != 0) {
          uVar9 = 0;
          do {
            if (0 < iVar4) {
              printk("RDD RAW DWORD%d:%08x\n",uVar9,piVar10[uVar9]);
              iVar4 = DebugLevel;
            }
            uVar9 = uVar9 + 1;
          } while (uVar9 != uVar8);
        }
        if (0 < iVar4) {
          printk("%s: RDD FuncLen:%u, len:%u, prefix:%08x, cnt:%u\n","MT_ATERFTestCB",param_2[1],
                 uVar1,param_2[2],param_2[3]);
        }
      }
      os_zero_mem(&local_3c,0x14);
      local_3c = param_2[2];
      local_38 = param_2[3];
      if (uVar1 != 0) {
        piVar6 = piVar10;
        do {
          piVar11 = piVar6 + 2;
          local_34._1_3_ = (undefined3)*piVar6;
          iStack_30._1_3_ = (undefined3)piVar6[1];
          iStack_30 = CONCAT31(iStack_30._1_3_,(char)((uint)*piVar6 >> 0x18));
          uStack_2c = (undefined1)((uint)piVar6[1] >> 0x18);
          MT_ATEInsertLog(param_1,&local_3c,4,0x14);
          local_34 = 1;
          piVar6 = piVar11;
        } while (piVar11 != piVar10 + uVar1 * 2);
      }
    }
switchD_0028a0a8_caseD_2:
    return 0;
  }
  if (10 < DAT_005f6a34) {
    if (DAT_005f6a34 == 0xc) goto switchD_0028a0a8_caseD_c;
    if (DAT_005f6a34 != 0x11) goto LAB_0028a690;
    goto switchD_0028a0a8_caseD_11;
  }
  if (DAT_005f6a34 != 1) {
    if (DAT_005f6a34 == 2) {
      return 0;
    }
LAB_0028a690:
    if (DebugLevel < 3) {
      return 0;
    }
    printk("%s: No RF Test Event %x Dump\n","MT_ATERFTestCB",*param_2);
    return 0;
  }
switchD_0028a0a8_caseD_1:
  if (param_2 == (int *)0xfffffff8) {
    return 0;
  }
  piVar10 = param_2 + 4;
  local_40 = (void *)0x0;
  if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
     (iVar4 = os_alloc_mem(param_1,&local_40,6000), iVar4 != 0)) {
    return iVar4;
  }
  iVar2 = DAT_005f6a38;
  iVar4 = DebugLevel;
  iVar3 = param_2[3];
  iVar5 = param_2[1];
  local_3c = param_2[2];
  uVar1 = iVar5 - 8U >> 2;
  DAT_005f6a38 = iVar2;
  local_38 = iVar3;
  if (DAT_005f6a38 == 0) {
    DAT_005f6a3c = iVar3;
    *(int *)(param_1 + 0xa3b894) = iVar3;
    if (iVar4 < 4) {
      iVar5 = param_2[1];
      DAT_005f6a38 = iVar2;
    }
    else {
      printk("[Recal][%08x][START]\n",iVar3);
      iVar5 = param_2[1];
    }
  }
  DAT_005f6a38 = DAT_005f6a38 + iVar5;
  bVar12 = DAT_005f6a38 != 0x2208;
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    if ((iVar3 + 0xfe000000U & 0xfdffffff) == 0 || (iVar3 + 0xf8000000U & 0xf7ffffff) == 0) {
      if (uVar1 != 0) {
LAB_0028a480:
        piVar6 = piVar10;
        do {
          if (2 < DebugLevel) {
            printk("[Recal][%08x][%08x]\n",iVar3,*piVar6);
          }
          piVar11 = piVar6 + 1;
          iStack_30 = *piVar6;
          *(int *)((int)local_40 + ((int)piVar6 - (int)piVar10)) = iStack_30;
          piVar6 = piVar11;
        } while (piVar11 != piVar10 + uVar1);
        goto LAB_0028a460;
      }
LAB_0028a200:
      if (iVar3 == 0x8000000) {
        sVar7 = (uVar1 & 0x3fff) * 4;
        if (2 < DebugLevel) {
          printk("[cal_type][DNL]Ofst = 0x%x, len=%d\n\n",
                 *(undefined4 *)("SetPartProfileParameters" + param_1),sVar7);
        }
        memcpy((void *)(*(int *)("SetPartProfileParameters" + param_1 + 4) +
                       *(int *)("SetPartProfileParameters" + param_1)),local_40,sVar7);
        *(size_t *)("SetPartProfileParameters" + param_1) =
             sVar7 + *(int *)("SetPartProfileParameters" + param_1);
      }
      else if (iVar3 == 0x2000000) {
        sVar7 = (uVar1 & 0x3fff) * 4;
        if (2 < DebugLevel) {
          printk("[cal_type][TSSI-2G]Ofst = 0x%x, len=%d\n\n",
                 *(undefined4 *)("SetPartProfileParameters" + param_1 + 8),sVar7);
        }
        memcpy((void *)(*(int *)("SetPartProfileParameters" + param_1 + 0xc) +
                       *(int *)("SetPartProfileParameters" + param_1 + 8)),local_40,sVar7);
        *(size_t *)("SetPartProfileParameters" + param_1 + 8) =
             sVar7 + *(int *)("SetPartProfileParameters" + param_1 + 8);
      }
      else {
        if (iVar3 != 0x4000000) goto LAB_0028a224;
        sVar7 = (uVar1 & 0x3fff) * 4;
        if (2 < DebugLevel) {
          printk("[cal_type][TSSI-5G]Ofst = 0x%x, len=%d\n\n",
                 *(undefined4 *)("SetPartProfileParameters" + param_1 + 0x10),sVar7);
        }
        memcpy((void *)(*(int *)("SetPartProfileParameters" + param_1 + 0x14) +
                       *(int *)("SetPartProfileParameters" + param_1 + 0x10)),local_40,sVar7);
        *(size_t *)("SetPartProfileParameters" + param_1 + 0x10) =
             sVar7 + *(int *)("SetPartProfileParameters" + param_1 + 0x10);
      }
    }
    else {
      if (iVar3 != 0x20000000) {
        if (uVar1 != 0) goto LAB_0028a3c4;
        goto LAB_0028a200;
      }
      if (uVar1 != 0) goto LAB_0028a480;
LAB_0028a224:
      if ("RTMPSetSTAPassPhrase"[param_1 + 3] != '\0') {
        if (iVar3 == 0x20000000) {
          sVar7 = (uVar1 & 0x3fff) * 4;
          memcpy((void *)(*(int *)("RTMPSetSTAPassPhrase" + param_1 + 8) +
                         *(int *)("RTMPSetSTAPassPhrase" + param_1 + 0xc)),local_40,sVar7);
          iVar4 = DebugLevel;
          *(size_t *)("RTMPSetSTAPassPhrase" + param_1 + 0xc) =
               sVar7 + *(int *)("RTMPSetSTAPassPhrase" + param_1 + 0xc);
          if (2 < iVar4) {
            printk("[cal_type][Pre_Cal]len=%d, PreCalOfst=%d\n\n",uVar1);
          }
          **(undefined4 **)("RTMPSetSTAPassPhrase" + param_1 + 4) =
               *(undefined4 *)("RTMPSetSTAPassPhrase" + param_1 + 0xc);
        }
        else if (iVar3 == 0x10000000) {
          sVar7 = (uVar1 & 0x3fff) * 4;
          if (2 < DebugLevel) {
            printk("[cal_type][TX_DPD], ofset=%x, len =%d\n",
                   *(undefined4 *)("RTMPSetSTAPassPhrase" + param_1 + 0x14),sVar7);
          }
          memcpy((void *)(*(int *)("RTMPSetSTAPassPhrase" + param_1 + 0x10) +
                         *(int *)("RTMPSetSTAPassPhrase" + param_1 + 0x14)),local_40,sVar7);
          *(size_t *)("RTMPSetSTAPassPhrase" + param_1 + 0x14) =
               sVar7 + *(int *)("RTMPSetSTAPassPhrase" + param_1 + 0x14);
        }
      }
    }
    os_free_mem(local_40);
  }
  else if (uVar1 != 0) {
LAB_0028a3c4:
    uVar8 = 0;
    do {
      if ((uVar8 & 1) == 0) {
        if (3 < DebugLevel) {
          printk("[Recal][%08x][%08x]",iVar3,*piVar10);
        }
        local_34 = *piVar10;
      }
      else {
        if (3 < DebugLevel) {
          printk("%08x\n",*piVar10);
        }
        iStack_30 = *piVar10;
        if ((*(uint *)(param_1 + 0xa39ffc) & 8) != 0) {
          MT_ATEInsertLog(param_1,&local_3c,8,0x10);
        }
      }
      uVar8 = uVar8 + 1;
      piVar10 = piVar10 + 1;
    } while (uVar8 < uVar1);
LAB_0028a460:
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) goto LAB_0028a200;
  }
  if (bVar12 || iVar3 != -0x80000000) {
    return 0;
  }
LAB_0028a25c:
  if ((DAT_005f6a34 == 1) && (3 < DebugLevel)) {
    printk("[Recal][%08x][END]\n",DAT_005f6a3c);
  }
  DAT_005f6a38 = 0;
  DAT_005f6a34 = 0;
  DAT_005f6a3c = 0;
  return 0;
}

