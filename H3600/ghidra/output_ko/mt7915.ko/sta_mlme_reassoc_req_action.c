// module: mt7915.ko
// function: sta_mlme_reassoc_req_action @ 0x7e6c0
// size: 1664 bytes
//

void sta_mlme_reassoc_req_action(undefined4 param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int *piVar10;
  int iVar11;
  undefined4 uVar12;
  undefined1 *puVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined1 *puVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined1 uStack_7e;
  undefined1 local_7d;
  undefined1 auStack_7c [2];
  undefined1 auStack_7a [2];
  int local_78;
  int local_74;
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
  
  iVar5 = *(int *)(param_2 + 0x92c);
  local_74 = 0;
  local_6c = 0;
  iVar2 = GetStaCfgByWdev(param_1,iVar5);
  if (iVar2 == 0) {
    printk(&_LC1,0x5b3);
    dump_stack();
    return;
  }
  assoc_fsm_state_transition(iVar5,0);
  iVar3 = FUN_0007e650(*(undefined4 *)(param_2 + 0x92c));
  if (iVar3 == 1) {
    return;
  }
  iVar3 = MlmeAssocReqSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908),&local_5e,auStack_7c,
                             &local_78,auStack_7a);
  if (iVar3 == 0) {
    if (2 < DebugLevel) {
      printk("ASSOC - MlmeReassocReqAction() sanity check failed. BUG!!!!\n");
    }
    cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),4,0x51);
  }
  local_4c = 0;
  local_44 = 0;
  local_58 = 0;
  local_54 = (uint)*(byte *)(iVar2 + 0x4165) << 0x10;
  local_50 = (uint)*(ushort *)(iVar5 + 0x18);
  local_48 = iVar5;
  RTMPWPARemoveAllKeys(param_1,iVar5);
  RTMPCancelTimer(iVar2 + 0x211ee8,&uStack_7e);
  iVar4 = os_alloc_mem(param_1,&local_6c,0x900);
  iVar3 = DebugLevel;
  if (iVar4 != 0) {
    if (2 < DebugLevel) {
      printk("ASSOC - MlmeReassocReqAction() allocate memory failed\n");
    }
    cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),4,0x52);
    return;
  }
  *(undefined4 *)(iVar2 + 0x413a) = local_5e;
  *(undefined2 *)(iVar2 + 0x413e) = local_5a;
  if (2 < iVar3) {
    printk("ASSOC - Send RE-ASSOC request...\n");
  }
  MgtMacHeaderInitExt(param_1,auStack_40,2,0,&local_5e,iVar2 + 0x1b,&local_5e);
  iVar7 = iVar2 + 0x21244e;
  iVar11 = iVar2 + 0x4139;
  iVar6 = iVar2 + 0x4176;
  iVar3 = iVar2 + 0x4177;
  iVar4 = iVar2 + 0x4119;
  puVar13 = &SsidIe;
  uVar12 = 1;
  uVar14 = 1;
  uVar8 = (uint)*(byte *)(iVar2 + 0x4139);
  uVar15 = 1;
  uVar17 = 1;
  puVar16 = &SupRateIe;
  uVar9 = (uint)*(byte *)(iVar2 + 0x4176);
  uVar18 = 0xffffffff;
  MakeOutgoingFrame(local_6c,&local_74,0x18,auStack_40,2,auStack_7c,2,auStack_7a,6,iVar7,1,&SsidIe,1
                    ,iVar11,uVar8,iVar4,1,&SupRateIe,1,iVar6,uVar9,iVar3,0xffffffff);
  if (*(char *)(iVar2 + 0x4183) != '\0') {
    MakeOutgoingFrame(local_6c + local_74,&local_70,1,&ExtRateIe,1,iVar2 + 0x4183,
                      *(char *)(iVar2 + 0x4183),iVar2 + 0x4184,0xffffffff,iVar7,uVar12,puVar13,
                      uVar14,iVar11,uVar8,iVar4,uVar15,puVar16,uVar17,iVar6,uVar9,iVar3,uVar18);
    local_74 = local_74 + local_70;
  }
  iVar3 = GetAssociatedAPByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  local_64 = 0;
  uVar1 = *(ushort *)(iVar2 + 0x2123d4);
  uVar12 = *(undefined4 *)(iVar3 + 0x17c);
  uVar15 = *(undefined4 *)(iVar3 + 0x3a4);
  uVar14 = *(undefined4 *)(iVar3 + 0x2c4);
  local_68 = CONCAT22(local_68._2_2_,uVar1);
  *(undefined1 *)(iVar3 + 0x562) = 0;
  *(undefined1 *)(iVar3 + 0x400) = 0;
  if (*(char *)(iVar3 + 0x55e) == '\0') {
    if (*(char *)(iVar3 + 0x55c) != '\0') {
LAB_0007ebc4:
      if ((uVar1 & 0x80) == 0) goto LAB_0007e980;
      goto LAB_0007ebdc;
    }
LAB_0007e978:
    if ((uVar1 & 0x40) == 0) goto LAB_0007e980;
  }
  else {
    if ((uVar1 & 0x80) == 0) {
      *(undefined1 *)(iVar3 + 0x400) = 1;
      if (*(char *)(iVar3 + 0x55c) == '\0') goto LAB_0007e980;
      goto LAB_0007ebc4;
    }
    if (*(char *)(iVar3 + 0x55c) == '\0') goto LAB_0007e978;
LAB_0007ebdc:
    *(undefined1 *)(iVar3 + 0x562) = 1;
    if (*(char *)(iVar2 + 0x2123d6) == '\0') goto LAB_0007e978;
  }
  *(undefined1 *)(iVar3 + 0x400) = 1;
LAB_0007e980:
  WPAMakeRSNIE(*(undefined4 *)(iVar2 + 0x14),iVar3 + 0x17c,iVar3);
  piVar10 = (int *)(iVar3 + 0x710);
  puVar16 = (undefined1 *)(iVar3 + 0x71e);
  *(undefined4 *)(iVar2 + 0x2124d4) = uVar12;
  *(undefined4 *)(iVar2 + 0x2124cc) = uVar14;
  *(undefined4 *)(iVar2 + 0x2124d0) = uVar15;
  puVar13 = (undefined1 *)(iVar3 + 0x720);
  iVar4 = local_74;
  do {
    piVar10 = piVar10 + 1;
    if (*piVar10 != 0) {
      MakeOutgoingFrame(local_6c + iVar4,&local_64,1,puVar16 + -2,1,puVar16,*puVar16,puVar13,
                        0xffffffff);
      iVar4 = local_64 + local_74;
      local_74 = iVar4;
    }
    puVar16 = puVar16 + 1;
    puVar13 = puVar13 + 0xff;
  } while ((undefined1 *)(iVar3 + 0x720) != puVar16);
  local_58 = local_6c + iVar4;
  iVar3 = build_wmm_cap_ie(param_1,&local_58);
  local_74 = iVar3 + local_74;
  if (((*(uint *)(iVar2 + 0x2123ec) & 1) != 0) && ((*(ushort *)(iVar5 + 0x18) & 0x18) != 0)) {
    local_7d = 0x1a;
    local_64 = 0x334c9000;
    if (*(char *)(iVar2 + 0x40e1) == '\x01') {
      local_7d = 0x1e;
      MakeOutgoingFrame(local_6c + local_74,&local_68,1,&WpaIe,1,&local_7d,4,&local_64,0x1a,
                        iVar2 + 0x4190,0xffffffff);
    }
    else {
      MakeOutgoingFrame(local_6c + local_74,&local_68,1,&HtCapIe,1,&local_7d,0x1a,iVar2 + 0x4190,
                        0xffffffff);
    }
    local_74 = local_68 + local_74;
    local_58 = local_6c + local_74;
    uVar12 = wlan_config_get_etxbf(iVar5);
    iVar3 = HcIsBfCapSupport(iVar5);
    if (iVar3 == 0) {
      wlan_config_set_etxbf(iVar5);
    }
    iVar3 = build_vht_ies(param_1,&local_58);
    local_74 = local_74 + iVar3;
    wlan_config_set_etxbf(iVar5,uVar12);
  }
  local_58 = local_6c + local_74;
  iVar3 = build_extended_cap_ie(param_1,&local_58,0);
  local_74 = iVar3 + local_74;
  iVar5 = build_vendor_ie(param_1,iVar5,local_6c + local_74,3);
  local_74 = iVar5 + local_74;
  MiniportMMRequest(param_1,0,local_6c);
  os_free_mem(local_6c);
  RTMPSetTimer(iVar2 + 0x211ee8,local_78 << 1);
  assoc_fsm_state_transition(*(undefined4 *)(param_2 + 0x92c),2);
  return;
}

