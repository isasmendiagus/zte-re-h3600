// module: mt7915.ko
// function: RTMPIoctlGetSiteSurvey @ 0x15d4b4
// size: 692 bytes
//

void RTMPIoctlGetSiteSurvey(int *param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  undefined1 auStack_38 [4];
  undefined4 local_34;
  int *local_2c [2];
  
  if ((param_1 == (int *)0x0) || (iVar5 = *param_1, iVar5 == 0)) {
    if (-1 < DebugLevel) {
      printk("RTMPGetSiteSurvey para error pAdapter =%p\n",param_1);
    }
  }
  else {
    iVar5 = get_wdev_by_ioctl_idx_and_iftype
                      (param_1,*(undefined4 *)(iVar5 + 0x3c),*(undefined4 *)(iVar5 + 0x38));
    if (iVar5 == 0) {
      if (-1 < DebugLevel) {
        printk("RTMPGetSiteSurvey para error wdev =%p\n",0);
      }
    }
    else {
      local_34 = HcGetBandByWdev();
      if (0 < DebugLevel) {
        printk("RTMPGetSiteSurvey=%d\n",local_34);
      }
      os_alloc_mem(0,local_2c,0x490c);
      if (local_2c[0] != (int *)0x0) {
        __memzero(local_2c[0],0x490c);
        *local_2c[0] = 0;
        *(undefined1 *)(local_2c[0] + 1) = 0;
        get_scan_ctrl_by_wdev(param_1,iVar5);
        iVar2 = scan_in_run_state(param_1,iVar5);
        if (iVar2 != 1) {
          *(undefined1 *)(local_2c[0] + 1) = 1;
          puVar3 = (uint *)get_scan_tab_by_wdev(param_1,iVar5);
          BssTableSortByRssi(puVar3,0);
          if (2 < DebugLevel) {
            printk("=====ap count=%d===\n",*puVar3);
          }
          if (*puVar3 != 0) {
            if (*local_2c[0] == 0x80) {
LAB_0015d708:
              printk("7915:too many ap around,return part!!!\n");
            }
            else {
              puVar7 = puVar3 + 2;
              piVar4 = local_2c[0] + *local_2c[0] * 0x24;
              if ((char)puVar3[5] != '\0') {
                iVar5 = 0xafc - (int)puVar7;
                uVar9 = 0;
                puVar8 = puVar3 + 0x2bf;
                do {
                  uVar9 = uVar9 + 1;
                  RTMPCommSiteSurveyData(piVar4 + 2,puVar7);
                  puVar7 = (uint *)((int)puVar3 + (int)puVar7 + iVar5);
                  *local_2c[0] = *local_2c[0] + 1;
                  if (*puVar3 <= uVar9) break;
                  if (*local_2c[0] == 0x80) goto LAB_0015d708;
                  puVar1 = puVar8 + 3;
                  piVar4 = local_2c[0] + *local_2c[0] * 0x24;
                  puVar8 = puVar8 + 0x2bd;
                } while ((char)*puVar1 != '\0');
              }
            }
          }
          HcGetAutoChCtrlbyBandIdx(param_1,local_34);
        }
        uVar9 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 0x490c;
        uVar6 = *(uint *)(((uint)auStack_38 & 0xffffe000) + 8);
        if (uVar9 < 0xffffb6f4 && uVar9 + 0x490c <= uVar6) {
          uVar6 = 0;
        }
        if (((uVar6 != 0) || (iVar5 = __copy_to_user(uVar9,local_2c[0]), iVar5 != 0)) &&
           (2 < DebugLevel)) {
          printk("%s: copy_to_user() fail\n","RTMPIoctlGetSiteSurvey");
        }
        os_free_mem(local_2c[0]);
        return;
      }
      if (-1 < DebugLevel) {
        printk("RTMPGetSiteSurvey pApTab memory alloc fail.\n");
      }
    }
  }
  return;
}

