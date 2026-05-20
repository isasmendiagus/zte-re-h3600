// module: mt7915.ko
// function: sta_mlme_assoc_req_action @ 0x7ed44
// size: 4920 bytes
//

void sta_mlme_assoc_req_action(int param_1,int param_2)

{
  undefined1 uVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char cVar7;
  void *pvVar8;
  void *__src;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined1 *puVar12;
  int iVar13;
  undefined1 *puVar14;
  int *piVar15;
  int iVar16;
  uint uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  int local_b4;
  undefined1 *local_a8;
  int local_a0;
  int *local_9c;
  int local_98;
  undefined1 uStack_7e;
  undefined1 local_7d;
  undefined1 local_7c;
  undefined1 local_7b;
  undefined2 local_7a;
  ushort local_78;
  ushort local_76;
  undefined4 local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  undefined4 local_5e;
  undefined2 local_5a;
  int local_58;
  int local_54;
  uint local_50;
  undefined4 local_4c;
  int local_48;
  undefined4 local_44;
  undefined1 auStack_40 [28];
  
  iVar10 = *(int *)(param_2 + 0x92c);
  local_70 = 0;
  local_6c = 0;
  iVar4 = GetStaCfgByWdev(param_1,iVar10);
  iVar5 = GetAssociatedAPByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  uVar1 = *(undefined1 *)(iVar10 + 0xe);
  local_7d = 0;
  local_7c = 1;
  local_7b = 0x32;
  if (iVar4 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s:pStaCfg=NULL,retuen!\n","sta_mlme_assoc_req_action");
    return;
  }
  if (0 < DebugLevel) {
    printk("%s:wdev(type=%d,idx=%d,func_idx=%d\n","sta_mlme_assoc_req_action",
           *(undefined4 *)(iVar10 + 0x14),*(undefined1 *)(iVar10 + 0xc),uVar1);
  }
  if (*(int *)(iVar10 + 0x14) == 0x100) {
    if (iVar5 == 0) {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s:ACPLI is not connected, return repeater connection\n","sta_mlme_assoc_req_action");
      return;
    }
    iVar13 = *(int *)(iVar10 + 4);
    if (iVar13 == 0) {
      printk(&_LC8,0x27e);
      dump_stack();
    }
    iVar11 = iVar13 + 8;
  }
  else {
    iVar13 = 0;
    iVar11 = iVar4 + 0x211eb4;
  }
  assoc_fsm_state_transition(iVar10,0);
  iVar6 = FUN_0007e650(iVar10);
  if (iVar6 == 1) {
    return;
  }
  iVar6 = MlmeAssocReqSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908),&local_5e,&local_78,
                             &local_74,&local_7a);
  if (iVar6 == 0) {
    if (2 < DebugLevel) {
      printk("ASSOC - MlmeAssocReqAction() sanity check failed. BUG!!!!!!\n");
    }
    cntl_auth_assoc_conf(iVar10,3,0x51);
    return;
  }
  if (*(int *)(iVar10 + 0x14) == 0x100) {
    iVar5 = MacTableInsertEntry(param_1,iVar4 + 0x413a,iVar13 + 0xe0,0x40001,1,1);
    if (iVar5 == 0) {
      if (DebugLevel < 0) {
        return;
      }
      printk("repeater pEntry insert fail");
      return;
    }
    if ((*(uint *)(iVar4 + 0x2c) & 0x2000) != 0) {
      iVar6 = *(int *)(iVar4 + 0x21246c);
      if (iVar6 != 0) {
        *(undefined4 *)(iVar5 + 0x563) = *(undefined4 *)(iVar6 + 0x563);
        *(undefined1 *)(iVar5 + 0x560) = *(undefined1 *)(iVar6 + 0x560);
      }
      pvVar8 = memmove((void *)(iVar5 + 0x30a),(void *)(iVar13 + 0x42b1),0x20);
      *(undefined1 *)(iVar5 + 0x55e) = 1;
      *(undefined1 *)(iVar5 + 0x55c) = 1;
      hex_dump_with_lvl("repeater mode: SecConfig.PMK:",pvVar8,0x20,3);
    }
    *(int *)(iVar13 + 0x4144) = iVar5;
    *(int *)(iVar5 + 0xafc) = iVar13;
  }
  local_4c = 0;
  local_44 = 0;
  local_58 = 0;
  local_54 = (uint)*(byte *)(iVar4 + 0x4165) << 0x10;
  local_50 = (uint)*(ushort *)(iVar10 + 0x18);
  local_48 = iVar10;
  RTMPCancelTimer(iVar11,&uStack_7e);
  *(undefined4 *)(iVar4 + 0x413a) = local_5e;
  *(undefined2 *)(iVar4 + 0x413e) = local_5a;
  iVar6 = os_alloc_mem(param_1,&local_70,0x900);
  if (iVar6 != 0) {
    if (2 < DebugLevel) {
      printk("ASSOC - MlmeAssocReqAction() allocate memory failed\n");
    }
    cntl_auth_assoc_conf(iVar10,3,0x52);
    return;
  }
  *(undefined4 *)(iVar4 + 0x21280c) = 0x28;
  *(undefined2 *)(iVar4 + 0x212810) = 3;
  *(undefined4 *)(iVar4 + 0x212820) = 0x28;
  *(ushort *)(iVar4 + 0x212812) = local_78;
  *(undefined2 *)(iVar4 + 0x212814) = local_7a;
  pvVar8 = (void *)(iVar4 + 0x4119);
  __memzero(iVar4 + 0x212836,0x400);
  iVar16 = iVar4 + 0x4176;
  *(undefined1 *)(iVar4 + 0x212836) = local_7d;
  *(undefined1 *)(iVar4 + 0x212837) = *(undefined1 *)(iVar4 + 0x4139);
  __src = (void *)(iVar4 + 0x4177);
  iVar6 = iVar4 + 0x4139;
  uVar9 = (uint)*(byte *)(iVar4 + 0x4139);
  memmove((void *)(iVar4 + 0x212838),pvVar8,uVar9);
  *(undefined1 *)(iVar4 + uVar9 + 0x212838) = local_7c;
  *(undefined1 *)(iVar4 + uVar9 + 0x212839) = *(undefined1 *)(iVar4 + 0x4176);
  memmove((void *)(iVar4 + uVar9 + 4 + 0x212836),__src,(uint)*(byte *)(iVar4 + 0x4176));
  local_98 = uVar9 + 4 + (uint)*(byte *)(iVar4 + 0x4176);
  if (*(byte *)(iVar10 + 0x1a) < 0xf) {
    local_78 = local_78 & 0xfeff;
    if (iVar10 != 0) {
      if (*(int *)(iVar10 + 0x14) != 2) {
        bVar3 = false;
        goto LAB_0007f180;
      }
      __ZTE_STA_Assoc_Process
                (param_1,0x17,&local_5e,0xffffffff,0,0,0,"sta_mlme_assoc_req_action",0x307);
    }
  }
  else {
    if (*(char *)(param_1 + 0x795074) != '\x01') {
      local_78 = local_78 & 0xfeff;
    }
    if (iVar10 != 0) {
      bVar3 = *(int *)(iVar10 + 0x14) == 2;
LAB_0007f180:
      if (*(byte *)(iVar10 + 0x1a) < 0xf) {
        bVar3 = false;
      }
      if (bVar3) {
        __ZTE_STA_Assoc_Process
                  (param_1,0x17,&local_5e,0xfffffffb,0,0,0,"sta_mlme_assoc_req_action",0x30b);
      }
    }
  }
  if (2 < DebugLevel) {
    printk("ASSOC - Send ASSOC request...\n");
  }
  MgtMacHeaderInitExt(param_1,auStack_40,0,0,&local_5e,iVar10 + 0x1b,&local_5e);
  puVar14 = &local_7c;
  uVar18 = 1;
  puVar12 = &local_7d;
  uVar9 = (uint)*(byte *)(iVar4 + 0x4139);
  uVar19 = 1;
  uVar20 = 1;
  uVar17 = (uint)*(byte *)(iVar4 + 0x4176);
  uVar21 = 0xffffffff;
  MakeOutgoingFrame(local_70,&local_6c,0x18,auStack_40,2,&local_78,2,&local_7a,1,puVar12,1,iVar6,
                    uVar9,pvVar8,1,puVar14,1,iVar16,uVar17,__src,0xffffffff);
  if (*(char *)(iVar4 + 0x4183) != '\0') {
    MakeOutgoingFrame(local_70 + local_6c,&local_68,1,&local_7b,1,iVar4 + 0x4183,
                      *(char *)(iVar4 + 0x4183),iVar4 + 0x4184,0xffffffff,puVar12,uVar18,iVar6,uVar9
                      ,pvVar8,uVar19,puVar14,uVar20,iVar16,uVar17,__src,uVar21);
    local_6c = local_6c + local_68;
  }
  iVar6 = DebugLevel;
  if (((*(char *)(param_1 + 0x795984) == '\0') || ((*(uint *)(iVar5 + 0x2c4) & 0x1e) == 0)) ||
     ((*(uint *)(iVar5 + 0x2c4) & 0x20) != 0)) {
LAB_0007f594:
    uVar9 = *(uint *)(iVar4 + 0x2123ec);
  }
  else {
    uVar9 = *(uint *)(iVar4 + 0x2123ec) & 0xfffffffa;
    *(uint *)(iVar4 + 0x2123ec) = uVar9;
    if (2 < iVar6) {
      printk("%s : Force STA as Non-HT mode\n","sta_mlme_assoc_req_action");
      goto LAB_0007f594;
    }
  }
  if (((uVar9 & 1) != 0) && ((*(ushort *)(iVar10 + 0x18) & 0x18) != 0)) {
    if (iVar13 != 0 && (&DAT_0036790d)[param_1] != '\0') {
      local_4c = CONCAT22(local_4c._2_2_,*(undefined2 *)(*(int *)(iVar13 + 0x4144) + 0xe0));
    }
    local_58 = local_70 + local_6c;
    iVar6 = build_ht_ies(param_1,&local_58);
    local_6c = iVar6 + local_6c;
    if (((*(char *)(param_1 + 0x79504c) != '\0') &&
        (printk("======================================> check WPA2PSK :%d\n",
                (*(uint *)(iVar5 + 0x17c) & 0x2090) != 0), (*(uint *)(iVar5 + 0x17c) & 0x2090) != 0)
        ) && ((*(int *)(iVar10 + 0x12e4) == 0 || (*(char *)(iVar10 + 0x3cc8) == '\0')))) {
      if ((*(uint *)(iVar4 + 0x2c) & 0x2000) != 0) {
        if (((&DAT_0036790d)[param_1] == '\0') || (*(int *)(iVar10 + 0x14) != 0x100)) {
          local_a0 = iVar4 + 0x212649;
          uVar2 = *(ushort *)(iVar4 + 0x2132e0);
          iVar16 = iVar4 + 0x2127ac;
          iVar6 = sta_search_pmkid_cache(param_1,&local_5e,uVar1,iVar10);
          local_a8 = (undefined1 *)((uint)uVar2 * 0x14c0 + param_1 + 0xa1d20);
          if (iVar6 == -1) goto LAB_0007fc10;
LAB_0007f8e0:
          _raw_spin_lock_bh(iVar16);
          local_a0 = iVar6 * 0x57 + local_a0;
          *(int *)((int)local_a8 + 0x708) = local_a0 + 6;
          *(int *)((int)local_a8 + 0x70c) = local_a0 + 0x16;
          _raw_spin_unlock_bh(iVar16);
        }
        else {
          local_a8 = *(undefined1 **)(iVar13 + 0x4144);
          iVar6 = sta_search_pmkid_cache(param_1,&local_5e,uVar1,iVar10);
          local_a0 = iVar13 + 0x414c;
          iVar16 = iVar13 + 0x42ac;
          if (iVar6 == -1) {
LAB_0007fc10:
            printk("PMKID not found in cache: Normal Assoc\n");
            *(undefined4 *)((int)local_a8 + 0x708) = 0;
            *(undefined4 *)((int)local_a8 + 0x70c) = 0;
          }
          else {
            if (iVar16 != 0) goto LAB_0007f8e0;
            local_a0 = iVar6 * 0x57 + local_a0;
            *(int *)((int)local_a8 + 0x708) = local_a0 + 6;
            *(int *)((int)local_a8 + 0x70c) = local_a0 + 0x16;
          }
        }
      }
      local_64 = 0;
      local_76 = *(ushort *)(iVar4 + 0x2123d4);
      *(undefined1 *)(iVar5 + 0x562) = 0;
      *(undefined1 *)(iVar5 + 0x400) = 0;
      uVar18 = *(undefined4 *)(iVar5 + 0x17c);
      uVar19 = *(undefined4 *)(iVar5 + 0x2c4);
      uVar20 = *(undefined4 *)(iVar5 + 0x3a4);
      if (*(char *)(iVar5 + 0x55e) == '\0') {
        cVar7 = '\0';
        if (*(char *)(iVar5 + 0x55c) == '\0') {
LAB_0007fac4:
          if ((local_76 & 0x40) != 0) goto LAB_0007f974;
        }
        else {
LAB_0007f984:
          if ((local_76 & 0x80) != 0) goto LAB_0007f98c;
        }
      }
      else {
        cVar7 = *(char *)(iVar5 + 0x55c);
        if ((local_76 & 0x80) == 0) {
LAB_0007f974:
          *(undefined1 *)(iVar5 + 0x400) = 1;
          if (cVar7 != '\0') goto LAB_0007f984;
        }
        else {
          if (cVar7 == '\0') goto LAB_0007fac4;
LAB_0007f98c:
          *(undefined1 *)(iVar5 + 0x562) = 1;
          if ((*(char *)(iVar4 + 0x2123d6) != '\0') || ((local_76 & 0x40) != 0)) {
            *(undefined1 *)(iVar5 + 0x400) = 1;
          }
        }
      }
      puVar12 = (undefined1 *)(iVar5 + 0x71e);
      WPAMakeRSNIE(*(undefined4 *)(iVar4 + 0x14),iVar5 + 0x17c,iVar5);
      local_9c = (int *)(iVar5 + 0x710);
      *(undefined4 *)(iVar4 + 0x2124d4) = uVar18;
      *(undefined4 *)(iVar4 + 0x2124cc) = uVar19;
      *(undefined4 *)(iVar4 + 0x2124d0) = uVar20;
      local_a8 = (undefined1 *)(iVar5 + 0x720);
      do {
        local_9c = local_9c + 1;
        if (*local_9c != 0) {
          MakeOutgoingFrame(local_70 + local_6c,&local_64,1,puVar12 + -2,1,puVar12,*puVar12,local_a8
                            ,0xffffffff);
          local_6c = local_6c + local_64;
        }
        puVar12 = puVar12 + 1;
        local_a8 = local_a8 + 0xff;
      } while ((undefined1 *)(iVar5 + 0x720) != puVar12);
      if (*(int *)(iVar4 + 0x5c4) == 0) {
        if (*(int *)(iVar4 + 0x5c8) == 0) goto LAB_0007f328;
        iVar6 = 1;
      }
      else {
        iVar6 = 0;
      }
      iVar16 = iVar4 + iVar6 + 0x5c8;
      *(undefined1 *)(iVar4 + local_98 + 0x212836) = *(undefined1 *)(iVar16 + 4);
      *(undefined1 *)(iVar4 + local_98 + 0x212837) = *(undefined1 *)(iVar16 + 6);
      memmove((void *)(iVar4 + local_98 + 2 + 0x212836),(void *)(iVar4 + iVar6 * 0xff + 0x5d0),
              (uint)*(byte *)(iVar4 + iVar6 + 0x5ce));
      local_98 = local_98 + 2 + (uint)*(byte *)(iVar4 + 0x213038);
      *(short *)(iVar4 + 0x212834) = (short)local_98;
    }
LAB_0007f328:
    if (((*(uint *)(iVar4 + 0x2123ec) & 1) != 0) && ((*(ushort *)(iVar10 + 0x18) & 0x18) != 0)) {
      local_58 = local_70 + local_6c;
      uVar18 = wlan_config_get_etxbf(iVar10);
      iVar6 = HcIsBfCapSupport(iVar10);
      if (iVar6 == 0) {
        wlan_config_set_etxbf(iVar10);
      }
      else if (((((&DAT_0036790d)[param_1] != '\0') &&
                (iVar6 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
                (*(byte *)(iVar6 + 0x96) & 2) != 0)) &&
               (wlan_config_set_etxbf(iVar10,2), iVar13 != 0)) &&
              (*(char *)(param_1 + 0xa786f8) == '\0')) {
        if (0 < DebugLevel) {
          printk("%s : OriginalAddress[0~5] = %02x:%02x:%02x:%02x:%02x:%02x\n",
                 "sta_mlme_assoc_req_action",*(undefined1 *)(iVar13 + 0x7d),
                 *(undefined1 *)(iVar13 + 0x7e),*(undefined1 *)(iVar13 + 0x7f),
                 *(undefined1 *)(iVar13 + 0x80),*(undefined1 *)(iVar13 + 0x81),
                 *(undefined1 *)(iVar13 + 0x82));
        }
        if ((*(int *)(iVar13 + 0x4144) != 0) &&
           (iVar6 = HcIsBfCapSupport(*(undefined4 *)(*(int *)(iVar13 + 0x4144) + 8)), iVar6 == 1)) {
          wlan_config_set_etxbf(iVar10,1);
          *(undefined1 *)(param_1 + 0xa786f8) = 1;
          *(undefined1 *)(param_1 + 0xa786f9) = *(undefined1 *)(iVar13 + 0xee);
        }
      }
      iVar6 = build_vht_ies(param_1,&local_58);
      local_6c = local_6c + iVar6;
      wlan_config_set_etxbf(iVar10,uVar18);
      if ((((*(ushort *)(iVar10 + 0x18) & 0x1c0) != 0) &&
          ((*(uint *)(iVar4 + 0x2123ec) & 0x10) != 0)) && (*(int *)(iVar10 + 0x14) != 0x100)) {
        iVar6 = add_assoc_req_he_ies(iVar10,local_70 + local_6c);
        local_6c = iVar6 + local_6c;
      }
    }
  }
  local_58 = local_70 + local_6c;
  iVar6 = build_extended_cap_ie(param_1,&local_58,0);
  local_6c = iVar6 + local_6c;
  iVar6 = build_vendor_ie(param_1,iVar10,local_70 + local_6c,3);
  local_6c = iVar6 + local_6c;
  local_58 = local_70 + local_6c;
  iVar6 = build_wmm_cap_ie(param_1,&local_58);
  local_6c = iVar6 + local_6c;
  if (((*(char *)(param_1 + 0x79504c) != '\0') ||
      (printk("======================================> check WPA2PSK :%d\n",
              (*(uint *)(iVar5 + 0x17c) & 0x2090) != 0), (*(uint *)(iVar5 + 0x17c) & 0x2090) == 0))
     || ((*(int *)(iVar10 + 0x12e4) != 0 && (*(char *)(iVar10 + 0x3cc8) != '\0'))))
  goto LAB_0007f470;
  if ((*(uint *)(iVar4 + 0x2c) & 0x2000) != 0) {
    if (((&DAT_0036790d)[param_1] == '\0') || (*(int *)(iVar10 + 0x14) != 0x100)) {
      uVar2 = *(ushort *)(iVar4 + 0x2132e0);
      iVar16 = iVar4 + 0x212649;
      iVar13 = iVar4 + 0x2127ac;
      iVar6 = sta_search_pmkid_cache(param_1,&local_5e,uVar1,iVar10);
      local_b4 = (uint)uVar2 * 0x14c0 + param_1 + 0xa1d20;
      if (iVar6 == -1) goto LAB_00080048;
LAB_0007fd18:
      _raw_spin_lock_bh(iVar13);
      iVar16 = iVar6 * 0x57 + iVar16;
      *(int *)(local_b4 + 0x708) = iVar16 + 6;
      *(int *)(local_b4 + 0x70c) = iVar16 + 0x16;
      _raw_spin_unlock_bh(iVar13);
    }
    else {
      local_b4 = *(int *)(iVar13 + 0x4144);
      iVar6 = sta_search_pmkid_cache(param_1,&local_5e,uVar1,iVar10);
      iVar16 = iVar13 + 0x414c;
      iVar13 = iVar13 + 0x42ac;
      if (iVar6 == -1) {
LAB_00080048:
        printk("PMKID not found in cache: Normal Assoc\n");
        *(undefined4 *)(local_b4 + 0x708) = 0;
        *(undefined4 *)(local_b4 + 0x70c) = 0;
      }
      else {
        if (iVar13 != 0) goto LAB_0007fd18;
        iVar16 = iVar6 * 0x57 + iVar16;
        *(int *)(local_b4 + 0x708) = iVar16 + 6;
        *(int *)(local_b4 + 0x70c) = iVar16 + 0x16;
      }
    }
  }
  local_64 = 0;
  local_76 = *(ushort *)(iVar4 + 0x2123d4);
  *(undefined1 *)(iVar5 + 0x562) = 0;
  *(undefined1 *)(iVar5 + 0x400) = 0;
  uVar18 = *(undefined4 *)(iVar5 + 0x17c);
  uVar19 = *(undefined4 *)(iVar5 + 0x2c4);
  uVar20 = *(undefined4 *)(iVar5 + 0x3a4);
  if (*(char *)(iVar5 + 0x55e) == '\0') {
    cVar7 = '\0';
    if (*(char *)(iVar5 + 0x55c) == '\0') {
LAB_0007ff64:
      if ((local_76 & 0x40) != 0) goto LAB_0007fda8;
    }
    else {
LAB_0007fdb8:
      if ((local_76 & 0x80) != 0) goto LAB_0007fdc0;
    }
  }
  else {
    cVar7 = *(char *)(iVar5 + 0x55c);
    if ((local_76 & 0x80) == 0) {
LAB_0007fda8:
      *(undefined1 *)(iVar5 + 0x400) = 1;
      if (cVar7 != '\0') goto LAB_0007fdb8;
    }
    else {
      if (cVar7 == '\0') goto LAB_0007ff64;
LAB_0007fdc0:
      *(undefined1 *)(iVar5 + 0x562) = 1;
      if ((*(char *)(iVar4 + 0x2123d6) != '\0') || ((local_76 & 0x40) != 0)) {
        *(undefined1 *)(iVar5 + 0x400) = 1;
      }
    }
  }
  WPAMakeRSNIE(*(undefined4 *)(iVar4 + 0x14),iVar5 + 0x17c,iVar5);
  piVar15 = (int *)(iVar5 + 0x710);
  puVar14 = (undefined1 *)(iVar5 + 0x71e);
  *(undefined4 *)(iVar4 + 0x2124d4) = uVar18;
  *(undefined4 *)(iVar4 + 0x2124cc) = uVar19;
  *(undefined4 *)(iVar4 + 0x2124d0) = uVar20;
  puVar12 = (undefined1 *)(iVar5 + 0x720);
  do {
    piVar15 = piVar15 + 1;
    if (*piVar15 != 0) {
      MakeOutgoingFrame(local_70 + local_6c,&local_64,1,puVar14 + -2,1,puVar14,*puVar14,puVar12,
                        0xffffffff);
      local_6c = local_6c + local_64;
    }
    puVar14 = puVar14 + 1;
    puVar12 = puVar12 + 0xff;
  } while ((undefined1 *)(iVar5 + 0x720) != puVar14);
  if (*(int *)(iVar4 + 0x5c4) == 0) {
    if (*(int *)(iVar4 + 0x5c8) == 0) goto LAB_0007f470;
    iVar5 = 1;
  }
  else {
    iVar5 = 0;
  }
  iVar13 = iVar4 + iVar5 + 0x5c8;
  *(undefined1 *)(iVar4 + local_98 + 0x212836) = *(undefined1 *)(iVar13 + 4);
  *(undefined1 *)(iVar4 + local_98 + 0x212837) = *(undefined1 *)(iVar13 + 6);
  memmove((void *)(iVar4 + local_98 + 2 + 0x212836),(void *)(iVar4 + iVar5 * 0xff + 0x5d0),
          (uint)*(byte *)(iVar4 + iVar5 + 0x5ce));
  *(ushort *)(iVar4 + 0x212834) = (short)(local_98 + 2) + (ushort)*(byte *)(iVar4 + 0x213038);
LAB_0007f470:
  local_58 = local_70 + local_6c;
  iVar4 = build_extra_ie(param_1,&local_58);
  local_6c = iVar4 + local_6c;
  local_58 = local_70 + local_6c;
  iVar4 = build_wsc_ie(param_1,&local_58);
  local_6c = iVar4 + local_6c;
  if (*(char *)(param_1 + 0xa7cbfa) == '\x01') {
    MAP_InsertZteFakeRrmIE(param_1,iVar10,local_70 + local_6c,&local_6c);
    MAP_InsertMapCapIE(param_1,iVar10,local_70 + local_6c,&local_6c);
  }
  MiniportMMRequest(param_1,0,local_70,local_6c);
  os_free_mem(local_70);
  if (2 < DebugLevel) {
    printk("%s:Set assoc Timeout(%ld)ms\n","sta_mlme_assoc_req_action",local_74);
  }
  RTMPSetTimer(iVar11,local_74);
  assoc_fsm_state_transition(iVar10,1);
  return;
}

