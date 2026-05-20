// module: mt7915.ko
// function: ap_probe_response_xmit @ 0x4b750
// size: 1896 bytes
//

undefined4 ap_probe_response_xmit(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  char *pcVar3;
  undefined1 *puVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  undefined1 *puVar11;
  undefined4 uVar12;
  undefined1 *puVar13;
  undefined4 uVar14;
  undefined1 *puVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  undefined2 local_64;
  undefined1 auStack_60 [8];
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  int local_48;
  undefined4 local_44;
  undefined1 auStack_40 [28];
  
  local_74 = 0;
  local_70 = 0;
  HcGetQloadCtrl();
  iVar6 = *(int *)(param_2 + 4);
  local_77 = 1;
  local_76 = 1;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  wlan_operate_get_addht(param_2);
  wlan_config_get_ht_bw(param_2);
  wlan_config_get_ht_bw(param_2);
  uVar1 = *(ushort *)(param_2 + 0x18);
  local_54._0_3_ = CONCAT12(*(undefined1 *)(param_2 + 0x1a),(undefined2)local_54);
  local_50 = CONCAT22(local_50._2_2_,uVar1);
  local_54 = CONCAT31(local_54._1_3_,5);
  local_48 = param_2;
  iVar2 = os_alloc_mem(param_1,&local_74,0x900);
  if (iVar2 == 0) {
    MgtMacHeaderInit(param_1,auStack_40,5,0,param_3,param_2 + 0x1b,param_2 + 0x21);
    uVar8 = (uint)*(byte *)(param_2 + 0xade);
    if (uVar1 == 2) {
      uVar8 = 4;
    }
    puVar15 = &DsIe;
    iVar2 = iVar6 + 0x4068;
    iVar7 = param_2 + 0x1a;
    puVar4 = &local_77;
    uVar17 = 1;
    uVar18 = 0xffffffff;
    local_75 = (undefined1)uVar8;
    iVar9 = param_2 + 0xadf;
    puVar11 = &SupRateIe;
    puVar13 = &local_75;
    uVar16 = 1;
    uVar10 = 1;
    uVar12 = 1;
    uVar14 = 1;
    MakeOutgoingFrame(local_74,&local_70,0x18,auStack_40,8,auStack_60,2,&DAT_00794c50 + param_1,2,
                      iVar6 + 0x408c,1,&SsidIe,1,iVar6 + 0x4089,*(undefined1 *)(iVar6 + 0x4089),
                      iVar2,1,&SupRateIe,1,puVar13,uVar8,iVar9,1,&DsIe,1,puVar4,1,iVar7,0xffffffff);
    if (*(char *)(param_2 + 0xaeb) != '\0' && uVar1 != 2) {
      MakeOutgoingFrame(local_74 + local_70,&local_6c,1,&ErpIe,1,&local_76,1,&DAT_0036b8a1 + param_1
                        ,1,&ExtRateIe,1,param_2 + 0xaeb,*(char *)(param_2 + 0xaeb),param_2 + 0xaec,
                        0xffffffff,iVar2,uVar10,puVar11,uVar12,puVar13,uVar8,iVar9,uVar14,puVar15,
                        uVar16,puVar4,uVar17,iVar7,uVar18);
      local_70 = local_6c + local_70;
    }
    iVar7 = build_rsn_ie(param_1,param_2,local_74 + local_70);
    iVar2 = local_74;
    local_70 = local_70 + iVar7;
    iVar7 = HcGetBandByWdev(param_2);
    make_multiple_bssid_ie
              (param_1,param_2,&local_70,iVar2,*(undefined4 *)(param_1 + (iVar7 + 0xd9e3a) * 4),1);
    if (((uVar1 & 0x18) != 0) && (*(char *)(param_2 + 0x891) != '\0')) {
      local_58 = local_74 + local_70;
      iVar2 = build_ht_ies(param_1,&local_58);
      local_70 = iVar2 + local_70;
    }
    local_58 = local_74 + local_70;
    iVar2 = build_extended_cap_ie(param_1,&local_58,*(char *)(param_3 + 0x33) == '\0');
    local_70 = local_70 + iVar2;
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      pcVar3 = (char *)HcGetQloadCtrl(param_1);
    }
    else {
      if (*(byte *)(param_2 + 0x1a) < 0xf) {
        uVar10 = 1;
      }
      else {
        uVar10 = 2;
      }
      pcVar3 = (char *)HcGetQloadCtrlByRf(param_1,uVar10);
    }
    if (*pcVar3 != '\0') {
      iVar2 = QBSS_LoadElementAppend
                        (param_1,local_74 + local_70,pcVar3,*(undefined1 *)(param_2 + 0xe));
      local_70 = iVar2 + local_70;
    }
    if (*(char *)(iVar6 + 0x4c58) != '\0') {
      MakeOutgoingFrame(local_74 + local_70,&local_68,*(undefined4 *)(iVar6 + 0x4c5c),
                        *(undefined4 *)(iVar6 + 0x4c64),0xffffffff);
      local_70 = local_68 + local_70;
      MakeOutgoingFrame(local_74 + local_70,&local_68,*(undefined4 *)(iVar6 + 0x4c60),
                        *(undefined4 *)(iVar6 + 0x4c68),0xffffffff);
      local_70 = local_68 + local_70;
    }
    local_58 = local_74 + local_70;
    iVar2 = build_wmm_cap_ie(param_1,&local_58);
    local_70 = iVar2 + local_70;
    if (*(char *)(param_2 + 0xb21) == '\x01') {
      RRM_InsertRRMEnCapIE
                (param_1,param_2,local_74 + local_70,&local_70,*(undefined1 *)(param_2 + 0xe));
      iVar2 = local_74 + local_70;
      uVar10 = get_regulatory_class
                         (param_1,*(undefined1 *)(iVar6 + 0x1a),*(undefined2 *)(iVar6 + 0x18),iVar6)
      ;
      InsertChannelRepIE(param_1,iVar2,&local_70,param_1 + 0x794c31,uVar10,0,uVar1,
                         *(undefined1 *)(param_2 + 0xe));
    }
    iVar2 = FUN_0004b3cc(param_1,param_2,local_74 + local_70);
    puVar4 = *(undefined1 **)(param_2 + 0x3fe4);
    local_70 = iVar2 + local_70;
    iVar2 = 0;
    if (puVar4 != (undefined1 *)0x0) {
      if (((*(byte *)(param_2 + 0x1a) < 0xf) || (*(char *)(param_1 + 0x795074) != '\x01')) ||
         (puVar4[4] != '\x01')) {
        iVar2 = 0;
      }
      else {
        iVar2 = local_74 + local_70;
        *(undefined1 *)(local_74 + local_70) = 0x25;
        *(undefined1 *)(iVar2 + 2) = 1;
        *(undefined1 *)(iVar2 + 1) = 3;
        *(undefined1 *)(iVar2 + 3) = *(undefined1 *)(param_2 + 0x1a);
        *(undefined1 *)(iVar2 + 4) = *puVar4;
        if (*(char *)(param_1 + 0x795948) == '\0') {
          iVar2 = 5;
        }
        else {
          local_68 = 0;
          local_64 = 0;
          build_ext_channel_switch_ie
                    (param_1,&local_68,*(undefined1 *)(param_2 + 0x1a),
                     *(undefined2 *)(param_2 + 0x18),param_2);
          memmove((void *)(iVar2 + 5),&local_68,6);
          iVar2 = 0xb;
        }
      }
    }
    local_70 = local_70 + iVar2;
    if (((uVar1 & 0x18) != 0) && (*(char *)(param_2 + 0x891) != '\0')) {
      if (*(char *)(param_1 + 0xa39fbb) == '\x01') {
        local_50._0_3_ = CONCAT12(1,(undefined2)local_50);
        local_58 = local_74 + local_70;
        iVar2 = build_ht_ies(param_1,&local_58);
        local_70 = local_70 + iVar2;
      }
      uVar10 = wlan_config_get_etxbf(param_2);
      iVar2 = HcIsBfCapSupport(param_2);
      if (iVar2 == 0) {
        wlan_config_set_etxbf(param_2);
      }
      txbf_bfee_cap_set(1,*(undefined1 *)(param_3 + 0x31),*(undefined1 *)(param_3 + 0x32));
      local_58 = local_74 + local_70;
      iVar2 = build_vht_ies(param_1,&local_58);
      local_70 = local_70 + iVar2;
      wlan_config_set_etxbf(param_2,uVar10);
      if (((*(ushort *)(param_2 + 0x18) & 0x1c0) != 0) && (*(char *)(param_2 + 0x891) != '\0')) {
        iVar2 = add_probe_rsp_he_ies(param_2,local_74,local_70);
        local_70 = iVar2 + local_70;
      }
    }
    local_58 = local_74 + local_70;
    iVar2 = build_wsc_ie(param_1,&local_58);
    local_70 = iVar2 + local_70;
    MAP_InsertMapZteIE(param_1,param_2,local_74 + local_70,&local_70);
    iVar2 = build_vendor_ie(param_1,param_2,local_74 + local_70,2);
    local_70 = local_70 + iVar2;
    iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(char *)(iVar2 + 0xf9) != '\0') {
      bVar5 = 0;
      do {
        bVar5 = bVar5 + 1;
        MiniportMMRequest(param_1,0,local_74,local_70);
      } while (bVar5 < *(byte *)(iVar2 + 0xf9));
    }
    os_free_mem(local_74);
    return 1;
  }
  return 0;
}

