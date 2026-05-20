// module: mt7915.ko
// function: sta_peer_assoc_rsp_action @ 0x7db84
// size: 2748 bytes
//

void sta_peer_assoc_rsp_action(int param_1,int param_2)

{
  byte *pbVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  int iVar12;
  uint uVar13;
  undefined4 uVar14;
  int iVar15;
  undefined4 uVar16;
  char *pcVar17;
  undefined4 *puVar18;
  char *pcVar19;
  char *local_88;
  undefined1 uStack_71;
  undefined1 uStack_70;
  undefined1 local_6f;
  ushort local_6e;
  short local_6c;
  undefined2 local_6a;
  int local_68;
  undefined1 auStack_63 [6];
  undefined4 local_5d;
  undefined2 local_59;
  undefined1 auStack_57 [11];
  char local_4c [4];
  undefined4 auStack_48 [7];
  char acStack_2c [8];
  
  local_6f = 0xff;
  local_68 = 0;
  iVar4 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  iVar15 = *(int *)(param_2 + 0x92c);
  uVar2 = *(undefined1 *)(iVar15 + 0xe);
  if (iVar4 == 0) {
    printk(&_LC1,0x788);
    dump_stack();
    return;
  }
  os_alloc_mem(param_1,&local_68,0x310);
  if (local_68 == 0) {
    if (DebugLevel < 1) {
      return;
    }
    printk("%s():mem alloc failed!\n","sta_peer_assoc_rsp_action");
    return;
  }
  __memzero(local_68,0x310);
  os_zero_mem(local_4c,0x24);
  iVar5 = PeerAssocRspSanity(iVar4,param_2,*(undefined4 *)(param_2 + 0x908),auStack_63,&local_6e,
                             &local_6c,&local_6a,&local_6f,local_4c,auStack_57,&uStack_70,local_68);
  if (iVar5 == 0) {
    if (2 < DebugLevel) {
      printk("ASSOC - %s() sanity check fail\n","sta_peer_assoc_rsp_action");
    }
    goto joined_r0x0007e470;
  }
  iVar5 = memcmp(auStack_63,(void *)(iVar4 + 0x413a),6);
  if (iVar5 != 0) goto joined_r0x0007e470;
  if (2 < DebugLevel) {
    printk("%s():ASSOC - receive ASSOC_RSP to me (status=%d)\n","sta_peer_assoc_rsp_action",local_6c
          );
  }
  iVar5 = *(int *)(iVar15 + 0x14);
  if ((iVar15 != 0) && (iVar5 == 2)) {
    if (*(byte *)(iVar15 + 0x1a) < 0xf) {
      __ZTE_STA_Assoc_Process
                (param_1,0x19,auStack_63,0xffffffff,local_6c + 200,0,0,"sta_peer_assoc_rsp_action",
                 0x7a3);
      iVar5 = *(int *)(iVar15 + 0x14);
    }
    else {
      __ZTE_STA_Assoc_Process
                (param_1,0x19,auStack_63,0xfffffffb,local_6c + 200,0,0,"sta_peer_assoc_rsp_action",
                 0x7a7);
      iVar5 = *(int *)(iVar15 + 0x14);
    }
  }
  if (iVar5 == 0x100) {
    iVar5 = *(int *)(iVar15 + 4) + 8;
  }
  else {
    iVar5 = iVar4 + 0x211eb4;
  }
  RTMPCancelTimer(iVar5,&uStack_71);
  if (local_6c == 0) {
    iVar12 = local_68 + 0x244;
    uVar6 = dot11_max_sup_rate(iVar12);
    iVar5 = MacTableLookup2(param_1,auStack_63,iVar15);
    if (iVar5 == 0) {
      printk(&_LC26,0x7e0);
      dump_stack();
      goto joined_r0x0007e470;
    }
    iVar7 = get_scan_tab_by_wdev(param_1,iVar15);
    uVar8 = BssTableSearch(iVar7,iVar5 + 0xec,*(undefined1 *)(iVar15 + 0x1a));
    if (uVar8 == 0xffffffff) {
      if (-1 < DebugLevel) {
        printk("ASSOC - Can\'t find BSS after receiving Assoc response\n");
      }
    }
    else {
      *(undefined1 *)(iVar5 + 0x9d8) = 0;
      __memzero(iVar5 + 0x9d9,0xff);
      if ((*(uint *)(iVar5 + 0x17c) & 0x12cf8) != 0 && uVar8 < 0x100) {
        uVar13 = (uint)*(ushort *)(iVar7 + uVar8 * 0xaf4 + 0xf4);
        if (uVar13 != 0) {
          pcVar17 = (char *)(iVar7 + uVar8 * 0xaf4 + 0xf6);
          uVar8 = 0;
          do {
            if (*pcVar17 == -0x23) {
              iVar7 = memcmp(pcVar17 + 2,&WPA_OUI,4);
              if ((iVar7 == 0) && ((*(uint *)(iVar5 + 0x17c) & 0x18) != 0)) {
                if (0xff < uVar8 + (byte)pcVar17[1] + 2) break;
                memmove((void *)(iVar5 + uVar8 + 0x9d9),pcVar17,(byte)pcVar17[1] + 2);
                iVar7 = DebugLevel;
                uVar8 = uVar8 + (byte)pcVar17[1] + 2 & 0xffff;
                *(char *)(iVar5 + 0x9d8) = (char)uVar8;
                if (2 < iVar7) {
                  printk("%s():=> Store RSN_IE for WPA SM negotiation\n","set_mlme_rsn_ie");
                }
              }
            }
            else if (((*pcVar17 == '0') && (iVar7 = memcmp(pcVar17 + 4,&RSN_OUI,3), iVar7 == 0)) &&
                    ((*(uint *)(iVar5 + 0x17c) & 0x120c0) != 0)) {
              if (0xff < uVar8 + (byte)pcVar17[1] + 2) break;
              memmove((void *)(iVar5 + uVar8 + 0x9d9),pcVar17,(byte)pcVar17[1] + 2);
              iVar7 = DebugLevel;
              uVar8 = uVar8 + (byte)pcVar17[1] + 2 & 0xffff;
              *(char *)(iVar5 + 0x9d8) = (char)uVar8;
              if (2 < iVar7) {
                printk("%s():=> Store RSN_IE for WPA2 SM negotiation\n","set_mlme_rsn_ie");
              }
            }
            pbVar1 = (byte *)(pcVar17 + 1);
            pcVar17 = pcVar17 + *pbVar1 + 2;
            uVar13 = uVar13 + (0xfffe - (uint)*pbVar1) & 0xffff;
          } while (uVar13 != 0);
        }
      }
      if (*(char *)(iVar5 + 0x9d8) == '\0') {
        if (2 < DebugLevel) {
          printk("%s():=> no RSN_IE\n","set_mlme_rsn_ie");
        }
      }
      else {
        hex_dump("RSN_IE",iVar5 + 0x9d9);
      }
    }
    iVar7 = local_68;
    uVar3 = local_6e;
    if ((*(byte *)(param_1 + 0x286294) & 3) == 3) {
      if (*(int *)(iVar15 + 0x14) != 2) goto LAB_0007de90;
      if (*(char *)(param_1 + 0xa7cbfa) == '\x01') {
        if ((*(byte *)(local_68 + 0x1a7) & 0x60) == 0) {
          *(byte *)(iVar4 + 0x2123e8) = *(byte *)(local_68 + 0x1a7) & 0x60;
        }
        else {
          *(undefined1 *)(iVar4 + 0x2123e8) = 1;
        }
        *(undefined1 *)(iVar4 + 0x2123f2) = *(undefined1 *)(local_68 + 0x1a8);
      }
      else {
        *(undefined1 *)(iVar4 + 0x2123e8) = 0;
      }
      iVar9 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar5 + 8));
      uVar8 = *(uint *)(iVar7 + 0x240) & 1;
      if (iVar9 == 0) {
        printk(&_LC27,0x109);
        dump_stack();
      }
      else {
        *(undefined1 *)(iVar9 + 0x4118) = 1;
        *(ushort *)(iVar9 + 0x416c) = uVar3 & 0x533;
        puVar11 = (undefined4 *)(iVar9 + 0x41e6);
        local_88 = local_4c;
        do {
          puVar18 = puVar11 + 4;
          pcVar17 = local_88 + 0x10;
          uVar16 = *(undefined4 *)(local_88 + 4);
          uVar10 = *(undefined4 *)(local_88 + 8);
          uVar14 = *(undefined4 *)(local_88 + 0xc);
          pcVar19 = local_88 + 0x10;
          *puVar11 = *(undefined4 *)local_88;
          puVar11[1] = uVar16;
          puVar11[2] = uVar10;
          puVar11[3] = uVar14;
          puVar11 = puVar18;
          local_88 = pcVar17;
        } while (pcVar19 != acStack_2c);
        *puVar18 = *(undefined4 *)pcVar17;
        check_legacy_rates(iVar7 + 0x244,iVar9 + 0x4176,iVar9);
        if (2 < DebugLevel) {
          pcVar17 = "%s===> 11n HT STA\n";
          if (uVar8 == 0) {
            pcVar17 = "%s===> legacy STA\n";
          }
          printk(pcVar17,"ApCliAssocPostProc");
        }
        if ((uVar8 != 0) && ((*(ushort *)(iVar9 + 0x18) & 0x18) != 0)) {
          RTMPCheckHt(param_1,*(undefined2 *)(iVar5 + 0xe0),iVar7 + 0x274,iVar7 + 0x28e);
        }
        uVar16 = HcGetOmacIdx(param_1,iVar9);
        chip_arch_set_aid(param_1,*(undefined2 *)(iVar5 + 0xf8),uVar16);
        RTMPZeroMemory((void *)(iVar9 + 0x41cc),0xc);
        RTMPZeroMemory((void *)(iVar9 + 0x41d8),5);
        *(uint *)(iVar9 + 0x2123ec) = *(uint *)(iVar9 + 0x2123ec) & 0xfffffff3;
        if (((*(ushort *)(iVar9 + 0x18) & 0x20) != 0) && ((*(uint *)(iVar7 + 0x240) & 0xc) == 0xc))
        {
          if (2 < DebugLevel) {
            printk("There is vht le at Assoc Rsp ifIndex=%d\n",*(undefined1 *)(iVar15 + 0xe));
          }
          memmove((void *)(iVar9 + 0x41cc),(void *)(iVar7 + 0x2a4),0xc);
          uVar8 = *(uint *)(iVar9 + 0x2123ec);
          *(uint *)(iVar9 + 0x2123ec) = uVar8 | 4;
          memmove((void *)(iVar9 + 0x41d8),(void *)(iVar7 + 0x2b0),5);
          *(uint *)(iVar9 + 0x2123ec) = uVar8 | 0xc;
        }
      }
      *(undefined2 *)(iVar4 + 0x416a) = local_6a;
      RTMPZeroMemory((void *)(iVar4 + 0x41cc),0xc);
      RTMPZeroMemory((void *)(iVar4 + 0x41d8),5);
      iVar7 = local_68;
      uVar8 = *(uint *)(iVar4 + 0x2123ec) & 0xfffffff3;
      *(uint *)(iVar4 + 0x2123ec) = uVar8;
      if (((*(ushort *)(iVar4 + 0x18) & 0x20) != 0) && ((*(uint *)(local_68 + 0x240) & 0xc) == 0xc))
      {
        memmove((void *)(iVar4 + 0x41cc),(void *)(local_68 + 0x2a4),0xc);
        *(uint *)(iVar4 + 0x2123ec) = uVar8 | 4;
        memmove((void *)(iVar4 + 0x41d8),(void *)(iVar7 + 0x2b0),5);
        *(uint *)(iVar4 + 0x2123ec) = uVar8 | 0xc;
      }
      uVar16 = 1;
      *(char *)(iVar4 + 0x41e6) = local_4c[0];
    }
    else if (*(int *)(iVar15 + 0x14) == 2) {
      uVar16 = 0;
      FUN_0007d3c8(param_1,auStack_63,local_6e,local_6a,local_4c,local_68,iVar5);
    }
    else {
LAB_0007de90:
      uVar16 = 1;
    }
    if ((local_4c[0] == '\0') || (*(char *)(iVar15 + 0x8d4) == '\0')) {
      *(uint *)(iVar5 + 0xb4) = *(uint *)(iVar5 + 0xb4) & 0xfffffffe;
    }
    else {
      *(uint *)(iVar5 + 0xb4) = *(uint *)(iVar5 + 0xb4) | 1;
    }
    StaUpdateMacTableEntry(param_1,iVar5,uVar6,local_68,local_6e);
    TRTableInsertEntry(param_1,*(undefined2 *)(iVar5 + 0xe0),iVar5);
    RTMPSetSupportMCS(param_1,uVar16,iVar5,iVar12,*(byte *)(local_68 + 0x240) & 4,local_68 + 0x2a4,
                      local_68 + 0x274,*(byte *)(local_68 + 0x240) & 1);
    uVar8 = *(uint *)(local_68 + 0x240);
    if ((uVar8 & 0x20) != 0) {
      parse_he_bss_color_info(iVar15);
      uVar8 = *(uint *)(local_68 + 0x240);
    }
    if ((uVar8 & 0x100) != 0) {
      update_peer_he_muedca_ies(iVar5,local_68 + 0x240);
    }
  }
  else if (((*(uint *)(iVar4 + 0x2124d4) & 0x6000) != 0) && (local_6c == 0x35 || local_6c == 0x28))
  {
    if (*(int *)(iVar15 + 0x14) == 0x100) {
      puVar11 = (undefined4 *)(*(int *)(iVar15 + 4) + 0x83);
      local_5d = *puVar11;
    }
    else {
      puVar11 = (undefined4 *)(iVar4 + 0x1b);
      local_5d = *puVar11;
    }
    local_59 = *(undefined2 *)(puVar11 + 1);
    iVar4 = sta_search_pmkid_cache(param_1,auStack_63,uVar2,iVar15);
    if (iVar4 != -1) {
      if (0 < DebugLevel) {
        printk("%s: Delete pmkid on assoc fail(incorrect pmkid)\n","sta_peer_assoc_rsp_action");
      }
      sta_delete_pmkid_cache(param_1,auStack_63,uVar2,iVar15);
    }
    iVar4 = search_sae_instance("pci_sw_int_handler" + param_1,&local_5d,auStack_63);
    if (iVar4 != 0) {
      if (0 < DebugLevel) {
        printk("%s: Delete Existing sae instance on assoc fail(incorrect pmkid)\n",
               "sta_peer_assoc_rsp_action");
      }
      delete_sae_instance(iVar4);
    }
  }
  assoc_fsm_state_transition(*(undefined4 *)(param_2 + 0x92c),0);
  cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),3,local_6c);
joined_r0x0007e470:
  if (local_68 != 0) {
    os_free_mem();
  }
  return;
}

