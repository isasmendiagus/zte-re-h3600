// module: mt7915.ko
// function: ComposeBcnPktTail @ 0xb4b90
// size: 1068 bytes
//

void ComposeBcnPktTail(int param_1,int param_2,int *param_3,int param_4)

{
  undefined1 uVar1;
  ushort uVar2;
  char *pcVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_48;
  int local_44;
  int local_40;
  undefined1 local_3c;
  undefined1 local_3a;
  ushort local_38;
  int local_30;
  
  local_48 = *param_3;
  iVar7 = *(int *)(param_2 + 0x3fe4);
  uVar2 = *(ushort *)(param_2 + 0x18);
  if (*(int *)(param_2 + 0x14) == 1) {
    iVar6 = *(int *)(param_2 + 4);
    uVar1 = *(undefined1 *)(param_2 + 0xe);
    if (iVar6 != 0) {
      local_3a = *(undefined1 *)(param_2 + 0x1a);
      local_3c = 8;
      local_38 = uVar2;
      local_30 = param_2;
      MakeCountryIe(param_1,param_2,&local_48);
      MakePwrConstraintIe(param_1,param_2,&local_48,param_4);
      if (iVar7 == 0) {
        return;
      }
      if (((*(byte *)(param_2 + 0x1a) < 0xf) || (*(char *)(param_1 + 0x795074) != '\x01')) ||
         (*(char *)(iVar7 + 4) != '\x01')) {
        *(undefined2 *)(param_2 + 0x982) = 0;
      }
      else {
        MakeChSwitchAnnounceIEandExtend(param_1,param_2,&local_48,param_4);
      }
      iVar7 = HcGetBandByWdev(param_2);
      make_multiple_bssid_ie
                (param_1,param_2,&local_48,param_4,*(undefined4 *)(param_1 + (iVar7 + 0xd9e3a) * 4),
                 0);
      if (*(char *)(param_2 + 0xb21) == '\x01') {
        RRM_InsertRRMEnCapIE(param_1,param_2,param_4 + local_48,&local_48,uVar1);
      }
      MakeChReportIe(param_1,param_2,&local_48,param_4);
      if (((*(char *)(param_2 + 0xaeb) != '\0' && uVar2 != 2) &&
          ((*(ushort *)(param_2 + 0x18) & 0x4e) != 0)) && (*(byte *)(param_2 + 0x1a) < 0xf)) {
        iVar7 = param_4 + local_48;
        *(undefined1 *)(param_4 + local_48) = 0x2a;
        local_48 = local_48 + 3;
        *(undefined1 *)(iVar7 + 1) = 1;
        iVar5 = *(int *)(param_2 + 0x14);
        if (iVar5 == 1) {
          *(undefined *)(iVar7 + 2) = (&DAT_0036b8a1)[param_1];
          iVar5 = *(int *)(param_2 + 0x14);
        }
        if (iVar5 == 2) {
          *(undefined1 *)(iVar7 + 2) = 4;
        }
      }
      MakeExtSuppRateIe(param_1,param_2,&local_48,param_4);
      ComposeRSNIE(param_1,param_2,&local_48,param_4);
      ComposeWPSIE(param_1,param_2,&local_48,param_4);
      if (*(char *)(param_1 + 0x79504d) == '\0') {
        pcVar3 = (char *)HcGetQloadCtrl(param_1);
      }
      else {
        if (*(byte *)(param_2 + 0x1a) < 0xf) {
          uVar4 = 1;
        }
        else {
          uVar4 = 2;
        }
        pcVar3 = (char *)HcGetQloadCtrlByRf(param_1,uVar4);
      }
      if ((pcVar3 != (char *)0x0) && (*pcVar3 != '\0')) {
        iVar7 = QBSS_LoadElementAppend(param_1,param_4 + local_48,pcVar3,uVar1);
        local_48 = local_48 + iVar7;
      }
      if (*(char *)(iVar6 + 0x4c58) != '\0') {
        MakeOutgoingFrame(param_4 + local_48,&local_44,*(undefined4 *)(iVar6 + 0x4c5c),
                          *(undefined4 *)(iVar6 + 0x4c64),0xffffffff);
        local_48 = local_44 + local_48;
        MakeOutgoingFrame(param_4 + local_48,&local_44,*(undefined4 *)(iVar6 + 0x4c60),
                          *(undefined4 *)(iVar6 + 0x4c68),0xffffffff);
        local_48 = local_48 + local_44;
      }
      if (((uVar2 & 0x18) != 0) && (*(char *)(param_2 + 0x891) != '\0')) {
        MakeHTIe(param_1,param_2,&local_48,param_4);
        local_40 = param_4 + local_48;
        iVar7 = build_vht_ies(param_1,&local_40);
        local_48 = iVar7 + local_48;
      }
      local_40 = param_4 + local_48;
      iVar7 = build_extended_cap_ie(param_1,&local_40,0);
      local_48 = iVar7 + local_48;
      if (*(char *)(param_2 + 0x8d4) != '\0') {
        MakeWmmIe(param_1,param_2,&local_48,param_4);
      }
      if (((*(ushort *)(param_2 + 0x18) & 0x1c0) != 0) && (*(char *)(param_2 + 0x891) != '\0')) {
        iVar7 = add_beacon_he_ies(param_2,param_4);
        local_48 = iVar7 + local_48;
      }
      iVar7 = build_vendor_ie(param_1,param_2,param_4 + local_48,0);
      local_48 = iVar7 + local_48;
      MAP_InsertMapZteIE(param_1,param_2,param_4 + local_48,&local_48);
      *param_3 = local_48;
      return;
    }
  }
  if (-1 < DebugLevel) {
    printk("%s - unexpected pMbss NULL, please check\n","ComposeBcnPktTail");
  }
  return;
}

