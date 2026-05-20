// module: mt7915.ko
// function: net_ad_rf_test_cb @ 0x25e530
// size: 1200 bytes
//

int net_ad_rf_test_cb(int param_1,int param_2,uint param_3,undefined4 *param_4,undefined4 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint uVar10;
  size_t sVar11;
  undefined4 *puVar12;
  void *local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  iVar3 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar3 == 0) {
    return 0x606;
  }
  DAT_005f641c = *param_4;
  switch(DAT_005f641c) {
  case 1:
    if (param_4 == (undefined4 *)0xfffffff8) {
      DAT_005f641c = 0;
      DAT_005f6420 = 0;
      DAT_005f6424 = 0;
      return 0;
    }
    local_40 = (void *)0x0;
    puVar12 = param_4 + 4;
    if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar3 + 0xc) & 0xffff) == 0x7915) &&
       (iVar6 = sys_ad_alloc_mem(&local_40,6000), iVar6 != 0)) {
      printk("%s: allocate cal_log memory fail\n","net_ad_rf_test_cb");
      if (local_40 != (void *)0x0) {
        sys_ad_free_mem();
        return iVar6;
      }
      return iVar6;
    }
    iVar4 = param_4[3];
    iVar5 = param_4[1];
    local_3c = param_4[2];
    iVar6 = iVar5;
    if (DAT_005f6420 == 0) {
      DAT_005f6424 = iVar4;
      *(int *)(param_2 + 0x40) = iVar4;
      iVar6 = iVar4;
    }
    uVar1 = iVar5 - 8U >> 2;
    if (DAT_005f6420 == 0) {
      iVar6 = param_4[1];
    }
    DAT_005f6420 = iVar6 + DAT_005f6420;
    local_38 = iVar4;
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar3 + 0xc) & 0xffff) == 0x7915) {
      if ((iVar4 + 0xfe000000U & 0xfdffffff) == 0 || (iVar4 + 0xf8000000U & 0xf7ffffff) == 0) {
        if (uVar1 != 0) {
LAB_0025e87c:
          puVar8 = puVar12;
          do {
            puVar9 = puVar8 + 1;
            local_30 = *puVar8;
            *(undefined4 *)((int)local_40 + ((int)puVar8 - (int)puVar12)) = local_30;
            puVar8 = puVar9;
          } while (puVar9 != puVar12 + uVar1);
          goto LAB_0025e5c8;
        }
        goto LAB_0025e5dc;
      }
      if (iVar4 != 0x20000000) {
        if (uVar1 != 0) goto LAB_0025e700;
        goto LAB_0025e5dc;
      }
      if (uVar1 != 0) goto LAB_0025e87c;
LAB_0025e600:
      if ("RTMPSetSTAPassPhrase"[iVar3 + 3] != '\0') {
        if (iVar4 == 0x20000000) {
          sVar11 = (uVar1 & 0x3fff) * 4;
          memcpy((void *)(*(int *)("RTMPSetSTAPassPhrase" + iVar3 + 8) +
                         *(int *)("RTMPSetSTAPassPhrase" + iVar3 + 0xc)),local_40,sVar11);
          *(size_t *)("RTMPSetSTAPassPhrase" + iVar3 + 0xc) =
               sVar11 + *(int *)("RTMPSetSTAPassPhrase" + iVar3 + 0xc);
          **(undefined4 **)("RTMPSetSTAPassPhrase" + iVar3 + 4) =
               *(undefined4 *)("RTMPSetSTAPassPhrase" + iVar3 + 0xc);
        }
        else if (iVar4 == 0x10000000) {
          sVar11 = (uVar1 & 0x3fff) * 4;
          memcpy((void *)(*(int *)("RTMPSetSTAPassPhrase" + iVar3 + 0x10) +
                         *(int *)("RTMPSetSTAPassPhrase" + iVar3 + 0x14)),local_40,sVar11);
          *(size_t *)("RTMPSetSTAPassPhrase" + iVar3 + 0x14) =
               sVar11 + *(int *)("RTMPSetSTAPassPhrase" + iVar3 + 0x14);
        }
      }
    }
    else {
      if (uVar1 == 0) {
        DAT_005f641c = 0;
        DAT_005f6420 = 0;
        DAT_005f6424 = 0;
        return 0;
      }
LAB_0025e700:
      uVar10 = 0;
      do {
        uVar7 = *puVar12;
        uVar2 = uVar7;
        if (((uVar10 & 1) != 0) && (uVar2 = local_34, local_30 = uVar7, (param_3 & 8) != 0)) {
          net_ad_insert_test_log(param_1,param_2 + 0x30,&local_3c,8,0x10);
          uVar2 = local_34;
        }
        local_34 = uVar2;
        uVar10 = uVar10 + 1;
        puVar12 = puVar12 + 1;
      } while (uVar10 < uVar1);
LAB_0025e5c8:
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar3 + 0xc) & 0xffff) != 0x7915) {
        DAT_005f641c = 0;
        DAT_005f6420 = 0;
        DAT_005f6424 = 0;
        return 0;
      }
LAB_0025e5dc:
      if (iVar4 == 0x8000000) {
        sVar11 = (uVar1 & 0x3fff) * 4;
        memcpy((void *)(*(int *)("SetPartProfileParameters" + iVar3 + 4) +
                       *(int *)("SetPartProfileParameters" + iVar3)),local_40,sVar11);
        *(size_t *)("SetPartProfileParameters" + iVar3) =
             sVar11 + *(int *)("SetPartProfileParameters" + iVar3);
      }
      else if (iVar4 == 0x2000000) {
        sVar11 = (uVar1 & 0x3fff) * 4;
        memcpy((void *)(*(int *)("SetPartProfileParameters" + iVar3 + 0xc) +
                       *(int *)("SetPartProfileParameters" + iVar3 + 8)),local_40,sVar11);
        *(size_t *)("SetPartProfileParameters" + iVar3 + 8) =
             sVar11 + *(int *)("SetPartProfileParameters" + iVar3 + 8);
      }
      else {
        if (iVar4 != 0x4000000) goto LAB_0025e600;
        sVar11 = (uVar1 & 0x3fff) * 4;
        memcpy((void *)(*(int *)("SetPartProfileParameters" + iVar3 + 0x14) +
                       *(int *)("SetPartProfileParameters" + iVar3 + 0x10)),local_40,sVar11);
        *(size_t *)("SetPartProfileParameters" + iVar3 + 0x10) =
             sVar11 + *(int *)("SetPartProfileParameters" + iVar3 + 0x10);
      }
    }
    sys_ad_free_mem(local_40);
    break;
  case 2:
    break;
  default:
    printk("%s: No RF Test Event %x Dump\n","net_ad_rf_test_cb");
    break;
  case 10:
    if ((param_3 & 4) != 0) {
      iVar3 = param_4[1];
      sys_ad_zero_mem(&local_3c);
      local_3c = param_4[2];
      local_38 = param_4[3];
      uVar1 = iVar3 - 0xcU >> 3;
      if (uVar1 != 0) {
        puVar12 = param_4 + 5;
        do {
          puVar8 = puVar12 + 2;
          sys_ad_move_mem((void *)((int)&local_34 + 1),puVar12,8);
          net_ad_insert_test_log(param_1,param_2 + 0x18,&local_3c,4,0x14);
          local_34 = CONCAT31(local_34._1_3_,1);
          puVar12 = puVar8;
        } while (puVar8 != param_4 + 5 + uVar1 * 2);
      }
    }
    break;
  case 0xc:
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar3 + 0xc) & 0xffff) == 0x7615) {
      ExtEventICapUnSolicitStatusHandler(iVar3,param_4,param_5);
    }
    break;
  case 0x11:
    RTEnqueueInternalCmd(iVar3,0x16,param_4,param_5);
  }
  DAT_005f6424 = 0;
  DAT_005f6420 = 0;
  DAT_005f641c = 0;
  return 0;
}

