// module: mt7915.ko
// function: RepeaterLinkMonitor @ 0x83438
// size: 996 bytes
//

void RepeaterLinkMonitor(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined *puVar11;
  undefined1 auStack_58 [16];
  undefined1 auStack_48 [36];
  
  iVar8 = *(int *)(&DAT_003687a8 + param_1);
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (((&DAT_0036790d)[param_1] != '\0' && iVar8 != 0) &&
     (uVar4 = (uint)*(byte *)(iVar3 + 0x14a), uVar4 != 0)) {
    uVar9 = 0;
    do {
      while( true ) {
        iVar8 = *(int *)(&DAT_003687a8 + param_1) + uVar9 * 0x42f4;
        cVar1 = *(char *)(*(int *)(&DAT_003687a8 + param_1) + uVar9 * 0x42f4);
        uVar10 = (uint)*(byte *)(*(int *)(iVar8 + 0x4140) + 0xe);
        if (cVar1 != '\0') break;
LAB_000834c0:
        uVar9 = uVar9 + 1 & 0xff;
        if (uVar4 <= uVar9) {
          return;
        }
      }
      if (*(int *)(iVar8 + 0x4144) != 0) {
        uVar4 = (uint)*(ushort *)(*(int *)(iVar8 + 0x4144) + 0xe0);
        if (DebugLevel < 3) {
          iVar6 = uVar4 << 3;
        }
        else {
          iVar6 = uVar4 * 8;
          printk("%s:repeater_entry(%d),p_sec(%d),wcid(%d),En(%d),Vld(%d)\n","RepeaterLinkMonitor",
                 *(undefined1 *)(iVar8 + 2),*(undefined1 *)(param_1 + uVar4 * 0x620 + 0x2f762),uVar4
                 ,cVar1,*(undefined1 *)(iVar8 + 1));
        }
        if (*(char *)(param_1 + (iVar6 - uVar4) * 0xe0 + 0x2f762) != '\x01') {
          if ((*(uint *)(&DAT_0057ff30 + param_1 + uVar10 * 0x2137b0) & 0x2000) == 0) {
            iVar6 = *(int *)(param_1 + 0x7960e8);
            iVar7 = *(int *)(iVar8 + 0x74);
LAB_000834ac:
            if (-1 < (iVar7 - iVar6) + 500) goto LAB_000834b8;
          }
          else {
            iVar7 = *(int *)(iVar8 + 0x74);
            iVar6 = *(int *)(param_1 + 0x7960e8);
            if (-1 < (iVar7 + 3000) - iVar6) goto LAB_000834ac;
          }
          if ((iVar8 == 0) || (*(char *)(iVar8 + 5) != '\x02')) {
            if (-1 < DebugLevel) {
              printk("%s:repeater_entry(%d),time(%ld),allocated->not linkup->overtime->del rp_entry\n"
                     ,"RepeaterLinkMonitor",*(undefined1 *)(iVar8 + 2),*(undefined4 *)(iVar8 + 0x74)
                    );
            }
            goto LAB_000835a4;
          }
          uVar5 = HcGetMaxStaNum(param_1);
          if (uVar4 < uVar5) {
            iVar6 = param_1 + uVar10 * 0x2137b0;
            if ((*(uint *)(&DAT_0057ff30 + iVar6) & 0x2000) != 0) {
              puVar11 = &DAT_00371c92 + iVar6;
              uVar2 = (&DAT_0036db66)[iVar6];
              iVar6 = sae_get_pmk_cache("pci_sw_int_handler" + param_1,iVar8 + 0x83,puVar11,
                                        auStack_58,auStack_48);
              if (iVar6 != 0) {
                iVar6 = sta_search_pmkid_cache(param_1,puVar11,uVar2);
                if (iVar6 != -1) {
                  iVar6 = search_sae_instance("pci_sw_int_handler" + param_1,iVar8 + 0x83,puVar11);
                  if (-1 < DebugLevel) {
                    printk("%s:Connection falied with pmkid ,delete cache entry and sae instance \n"
                           ,"RepeaterLinkMonitor");
                  }
                  if (iVar6 != 0) {
                    delete_sae_instance(iVar6);
                  }
                  sta_delete_pmkid_cache(param_1,puVar11,uVar2,iVar8 + 0xe0);
                }
              }
            }
            if (-1 < DebugLevel) {
              printk("%s:repeater_entry(%d),time(%ld),allocated->linkup->overtime->disconnect\n",
                     "RepeaterLinkMonitor",*(undefined1 *)(iVar8 + 2),*(undefined4 *)(iVar8 + 0x74))
              ;
            }
            RepeaterDisconnectRootAP(param_1,iVar8,1);
            uVar4 = (uint)*(byte *)(iVar3 + 0x14a);
            goto LAB_000834c0;
          }
        }
LAB_000834b8:
        uVar4 = (uint)*(byte *)(iVar3 + 0x14a);
        goto LAB_000834c0;
      }
      if ((-1 < (*(int *)(iVar8 + 0x74) - *(int *)(param_1 + 0x7960e8)) + 500) ||
         (*(char *)(iVar8 + 1) != '\0')) goto LAB_000834c0;
      if (-1 < DebugLevel) {
        printk("%s:repeater_entry(%d),pMacEntry(NULL),En(%d),Vld(%d)\n","RepeaterLinkMonitor",
               *(undefined1 *)(iVar8 + 2),cVar1,0);
      }
LAB_000835a4:
      HW_REMOVE_REPT_ENTRY(param_1,uVar9);
      uVar9 = uVar9 + 1 & 0xff;
      uVar4 = (uint)*(byte *)(iVar3 + 0x14a);
    } while (uVar9 < uVar4);
  }
  return;
}

