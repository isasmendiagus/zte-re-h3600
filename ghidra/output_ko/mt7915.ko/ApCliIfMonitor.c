// module: mt7915.ko
// function: ApCliIfMonitor @ 0x6b864
// size: 1288 bytes
//

void ApCliIfMonitor(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  int iVar12;
  uint local_64;
  undefined1 auStack_58 [16];
  undefined1 auStack_48 [36];
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(uint *)(param_1 + 0xa39f84) & 0x10000040) == 0x10000000) {
    puVar10 = &DAT_0036db58 + param_1;
    puVar11 = &DAT_0057ff80 + param_1;
    iVar12 = 0;
    do {
      if ((((puVar10[0xaa8] != '\0') && (iVar4 = scan_in_run_state(param_1,puVar10), iVar4 != 1)) &&
          (puVar11[0xf0c] == '\x01')) && (RepeaterLinkMonitor(param_1), puVar11[0xf0e] == '\x01')) {
        uVar7 = (uint)*(ushort *)(puVar11 + 0xeb8);
        uVar5 = HcGetMaxStaNum(param_1);
        if (uVar7 < uVar5) {
          uVar5 = 0;
          if ((*(uint *)(uVar7 * 0x14c0 + param_1 + 0xa1e9c) & 0x12cf8) != 0) {
            if (*(char *)(uVar7 * 0x620 + param_1 + 0x2f762) == '\x01') {
              uVar5 = 0;
            }
            else {
              uVar5 = (uint)((3000 - *(int *)(param_1 + 0x7960e8)) + *(int *)(puVar11 + 0xf20)) >>
                      0x1f;
            }
          }
          if ((puVar11[0x98] == '\0') &&
             ((0x4b0 - *(int *)(param_1 + 0x7960e8)) + *(int *)(puVar11 + 0xf18) < 0)) {
            if (2 < DebugLevel) {
              printk("STA Beacon loss condition got hit.\n");
              local_64 = uVar7;
            }
            if (uVar5 != 1) {
              local_64 = 1;
            }
            uVar8 = 1;
            *(undefined1 *)(uVar7 * 0x14c0 + param_1 + 0xa3148) = 0;
            if (uVar5 == 1) {
LAB_0006ba68:
              local_64 = uVar8;
              if ((*(uint *)(puVar11 + 0xac) & 0x2000) != 0) {
                puVar9 = puVar11 + -0x20e2ee;
                uVar1 = puVar10[0xe];
                iVar4 = sae_get_pmk_cache("pci_sw_int_handler" + param_1,puVar11 + -0x21240d,puVar9,
                                          auStack_58,auStack_48);
                if ((iVar4 != 0) &&
                   (iVar4 = sta_search_pmkid_cache(param_1,puVar9,uVar1,puVar10), iVar4 != -1)) {
                  iVar4 = search_sae_instance("pci_sw_int_handler" + param_1,puVar11 + -0x21240d,
                                              puVar9);
                  if (-1 < DebugLevel) {
                    printk("Reconnection falied with pmkid ,delete cache entry and sae instance \n")
                    ;
                  }
                  if (iVar4 != 0) {
                    delete_sae_instance(iVar4);
                  }
                  sta_delete_pmkid_cache(param_1,puVar9,uVar1,puVar10);
                }
              }
            }
            if ((2 < DebugLevel) &&
               (printk("ApCliIfMonitor: IF(apcli%d) - no Beancon is received from root-AP.\n",iVar12
                      ), 2 < DebugLevel)) {
              printk("ApCliIfMonitor: Reconnect the Root-Ap again.\n");
            }
            if (local_64 == 0) {
              if ((&DAT_0036790d)[param_1] != '\0') {
                uVar6 = HcGetBandByWdev(puVar10);
                repeater_disconnect_by_band(param_1,uVar6);
              }
              *(undefined4 *)(puVar11 + 0xf28) = 10;
            }
            else {
              if (DebugLevel < 3) {
LAB_0006bb68:
                if (2 < DebugLevel) {
                  printk("ApCliIfMonitor apcli%d time now: %lu\n",iVar12,jiffies);
                }
LAB_0006bb80:
                cVar2 = (&DAT_0036790d)[param_1];
              }
              else {
                printk("ApCliIfMonitor apcli%d time1: %lu\n",iVar12,*(undefined4 *)(puVar11 + 0xf10)
                      );
                if (2 < DebugLevel) {
                  printk("ApCliIfMonitor apcli%d time2: %lu\n",iVar12,
                         *(undefined4 *)(puVar11 + 0xf14));
                  if (DebugLevel < 3) goto LAB_0006bb80;
                  printk("ApCliIfMonitor apcli%d time3: %lu\n",iVar12,
                         *(undefined4 *)(puVar11 + 0xf18));
                  if (2 < DebugLevel) {
                    printk("ApCliIfMonitor apcli%d OS_HZ: %d\n",iVar12,100);
                    goto LAB_0006bb68;
                  }
                }
                cVar2 = (&DAT_0036790d)[param_1];
              }
              if (cVar2 != '\0') {
                uVar6 = HcGetBandByWdev(puVar10);
                repeater_disconnect_by_band(param_1,uVar6);
              }
              *(undefined4 *)(puVar11 + 0xf28) = 5;
            }
            __cntl_disconnect_request(puVar10,1,puVar11,8,"ApCliIfMonitor",0xb18);
          }
          else {
            iVar4 = param_1 + uVar7 * 0x14c0;
            if (uVar5 == 1) {
              uVar8 = 0;
              goto LAB_0006ba68;
            }
            if (puVar11[0x98] == '\0') {
              ApCliRTMPSendNullFrame
                        (param_1,*(undefined1 *)(iVar4 + 0xa289f),*(uint *)(iVar4 + 0xa1dd4) & 1,
                         param_1 + uVar7 * 0x14c0 + 0xa1d20,0);
            }
          }
        }
      }
      puVar11 = puVar11 + 0x2137b0;
      puVar10 = puVar10 + 0x2137b0;
      iVar12 = iVar12 + 1;
    } while (puVar11 != (undefined *)(param_1 + 0x9a6ee0));
    if (4 < DebugLevel) {
      printk("ra offload=%d\n",*(undefined1 *)(iVar3 + 0x150));
    }
  }
  return;
}

