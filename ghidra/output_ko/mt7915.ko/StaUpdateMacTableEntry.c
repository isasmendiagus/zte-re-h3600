// module: mt7915.ko
// function: StaUpdateMacTableEntry @ 0x148f5c
// size: 1564 bytes
//

undefined4
StaUpdateMacTableEntry(int param_1,int param_2,undefined4 param_3,int param_4,undefined2 param_5)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  ushort uVar6;
  int iVar7;
  void *pvVar8;
  bool bVar9;
  undefined4 local_38;
  int local_34;
  
  if (param_2 == 0) {
    return 0;
  }
  iVar7 = *(int *)(param_2 + 8);
  if (iVar7 == 0) {
    local_34 = 0;
  }
  else {
    local_34 = *(int *)(iVar7 + 4);
    if ((local_34 != 0) && (*(int *)(iVar7 + 0x14) != 2)) {
      if (*(int *)(iVar7 + 0x14) == 0x100) {
        local_34 = *(int *)(*(int *)(local_34 + 0x4140) + 4);
      }
      else {
        local_34 = 0;
      }
    }
  }
  if ((*(uint *)(param_1 + 0x795124) & 2) != 0) {
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) & 0xfffffffe;
  }
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar5 = dot11_2_ra_rate(param_3);
  bVar9 = uVar5 == 3;
  if (uVar5 < 4) {
    bVar9 = *(ushort *)(iVar7 + 0x18) == 4;
  }
  if (bVar9) {
    return 0;
  }
  if (((*(ushort *)(iVar7 + 0x18) & 0xffc7) == 0) && ((*(uint *)(param_4 + 0x240) & 1) == 0)) {
    return 0;
  }
  _raw_spin_lock_bh(param_1 + 0x285958);
  uVar1 = *(ushort *)(param_2 + 0xe0);
  __memzero(param_2 + 0x50c,8);
  *(undefined1 *)(param_1 + (uint)uVar1 * 0x620 + 0x2f762) = 1;
  if (uVar5 < 4) {
    bVar2 = (byte)uVar5 & 0x3f;
    *(undefined1 *)(param_2 + 0xb7c) = 4;
  }
  else {
    if (*(short *)(iVar7 + 0x18) != 2) {
      *(undefined2 *)(param_2 + 0xc0) = 0;
      *(undefined2 *)(param_2 + 0xbc) = 0;
      *(undefined2 *)(param_2 + 0xbe) = 0;
      *(byte *)(param_2 + 0xb7d) = (byte)uVar5;
      *(undefined1 *)(param_2 + 0xbf) = 0x20;
      *(undefined1 *)(param_2 + 0xb7c) = 0xc;
      bVar2 = OfdmRateToRxwiMCS[uVar5];
      *(byte *)(param_2 + 0xc1) = *(byte *)(param_2 + 0xc1) & 0x1f | 0x20;
      *(byte *)(param_2 + 0xbe) = bVar2 & 0x3f;
      bVar2 = OfdmRateToRxwiMCS[uVar5];
      *(byte *)(param_2 + 0xbd) = *(byte *)(param_2 + 0xbd) & 0x1f | 0x20;
      *(byte *)(param_2 + 0xc0) = *(byte *)(param_2 + 0xc0) & 0xc0 | bVar2 & 0x3f;
      *(byte *)(param_2 + 0xbc) = *(byte *)(param_2 + 0xbc) & 0xc0 | OfdmRateToRxwiMCS[uVar5] & 0x3f
      ;
      goto LAB_0014910c;
    }
    uVar5 = 3;
    bVar2 = 3;
    *(undefined1 *)(param_2 + 0xb7c) = 4;
  }
  *(byte *)(param_2 + 0xbe) = bVar2;
  *(byte *)(param_2 + 0xc0) = bVar2;
  *(byte *)(param_2 + 0xbc) = bVar2;
  *(char *)(param_2 + 0xb7d) = (char)uVar5;
  *(undefined1 *)(param_2 + 0xbf) = 0;
  *(undefined1 *)(param_2 + 0xc1) = 0;
  *(undefined1 *)(param_2 + 0xbd) = 0;
LAB_0014910c:
  *(undefined2 *)(param_2 + 0xaf6) = param_5;
  *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) & 0xfffffff9;
  __memzero((void *)(param_2 + 0xca4),0x1a);
  if (((((*(uint *)(param_2 + 0x2c4) & 0x1e) == 0) || (*(char *)(param_1 + 0x795984) == '\0')) &&
      ((*(char *)(local_34 + 0x4060) == '\x01' ||
       ((*(char *)(local_34 + 0x4060) == '\0' && (*(char *)(local_34 + 0x40ac) == '\x01')))))) &&
     (((*(uint *)(param_4 + 0x240) & 1) != 0 && ((*(ushort *)(iVar7 + 0x18) & 0x18) != 0)))) {
    pvVar8 = (void *)(param_4 + 0x274);
    if ((*(uint *)(param_1 + 0x795124) & 2) != 0) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 1;
    }
    ht_mode_adjust(param_1,param_2,pvVar8);
    if (*(char *)(iVar4 + 0x96) == '\0') {
      local_38 = 0;
    }
    else {
      local_38 = mt_WrapClientSupportsETxBF(param_1,param_4 + 0x289);
    }
    bVar2 = get_ht_max_mcs(iVar7 + 0x893,param_4 + 0x277);
    *(byte *)(param_2 + 0xbe) = *(byte *)(param_2 + 0xbe) & 0xc0 | bVar2 & 0x3f;
    bVar2 = *(byte *)(iVar7 + 0x8ae) & 0x7f;
    if (bVar2 != 0x21) {
      set_ht_fixed_mcs(param_2,bVar2,*(byte *)(iVar7 + 0x8b2) & 0x3f);
    }
    *(undefined2 *)(param_2 + 0xbc) = *(undefined2 *)(param_2 + 0xbe);
    set_sta_ht_cap(param_1,param_2,pvVar8);
    memmove((void *)(param_2 + 0xca4),pvVar8,0x1a);
    assoc_ht_info_debugshow(param_1,param_2,pvVar8);
    uVar6 = *(ushort *)(iVar7 + 0x18);
    if (((uVar6 & 0x20) != 0) && ((*(uint *)(param_4 + 0x240) & 0xc) == 0xc)) {
      pvVar8 = (void *)(param_4 + 0x2a4);
      vht_mode_adjust(param_1,param_2,pvVar8);
      dot11_vht_mcs_to_internal_mcs(param_1,iVar7,pvVar8,param_2 + 0xbe);
      set_vht_cap(param_1,param_2,pvVar8);
      memmove((void *)(param_2 + 0xd14),pvVar8,0xc);
      assoc_vht_info_debugshow(param_1,param_2,pvVar8,param_4 + 0x2b0);
      uVar6 = *(ushort *)(iVar7 + 0x18);
    }
    if (((uVar6 & 0x1c0) != 0) && ((*(uint *)(param_4 + 0x240) & 0x10) != 0)) {
      update_peer_he_caps(param_2,param_4 + 0x240);
      update_peer_he_operation(param_2,param_4 + 0x240);
      he_mode_adjust(iVar7,param_2);
    }
  }
  else {
    local_38 = 0;
    *(undefined1 *)(param_1 + 0x285942) = 1;
  }
  *(undefined2 *)(param_2 + 0xbc) = *(undefined2 *)(param_2 + 0xbe);
  *(undefined1 *)(param_2 + 0xb7f) = *(undefined1 *)(param_2 + 0xb7d);
  *(undefined2 *)(param_2 + 0x176) = 0;
  mt_WrapTxBFInit(param_1,param_2,param_4,local_38);
  iVar4 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar4 == 2) {
    if (*(char *)(iVar7 + 0x8b0) == '\x01') {
      *(undefined1 *)(param_2 + 0xb7e) = 1;
    }
    else {
      *(byte *)(param_2 + 0xbc) = *(byte *)(param_2 + 0xbc) & 0xc0 | *(byte *)(iVar7 + 0x8b2) & 0x3f
      ;
      bVar2 = *(byte *)(iVar7 + 0x8b3);
      *(undefined1 *)(param_2 + 0xb7e) = 0;
      bVar2 = bVar2 >> 5;
      *(byte *)(param_2 + 0xbd) = *(byte *)(param_2 + 0xbd) & 0x1f | bVar2 << 5;
      if (3 < bVar2) {
        bVar2 = *(byte *)(iVar7 + 0x8ae);
        cVar3 = wlan_operate_get_tx_stream(iVar7);
        *(byte *)(param_2 + 0xbc) =
             *(byte *)(param_2 + 0xbc) & 0xc0 | (bVar2 & 0x7f) + (cVar3 + -1) * '\x10' & 0x3f;
      }
      RTMPUpdateLegacyTxSetting(((uint)*(byte *)(iVar7 + 0x8af) << 0x1a) >> 0x1d,param_2);
    }
  }
  *(undefined1 *)(param_1 + (uint)uVar1 * 0x620 + 0x2f762) = 1;
  *(undefined4 *)(param_2 + 0x104) = 1;
  *(undefined4 *)(param_2 + 0xfc) = 2;
  if ((((*(int *)(param_2 + 0x1430) != 0) || (*(char *)(param_2 + 0x1434) != '\0')) ||
      (*(int *)(param_2 + 0x1438) != 0)) || (*(char *)(param_2 + 0x143c) != '\0')) {
    if (-1 < DebugLevel) {
      uVar5 = (uint)*(byte *)(param_2 + 0x1434);
      printk("@@@ %s(): (wcid=%u), HTC_ICVErrCnt(%u), HTC_AAD_OM_Freeze(%u)\n",
             "StaUpdateMacTableEntry",*(undefined2 *)(param_2 + 0xe0),*(int *)(param_2 + 0x1430),
             uVar5);
      if (-1 < DebugLevel) {
        printk(", HTC_AAD_OM_CountDown(%u),  HTC_AAD_OM_Freeze(%u) is in Asso. stage!\n",
               *(undefined4 *)(param_2 + 0x1438),*(undefined1 *)(param_2 + 0x143c),DebugLevel,uVar5)
        ;
      }
    }
    *(undefined4 *)(param_2 + 0x1430) = 0;
    *(undefined1 *)(param_2 + 0x1434) = 0;
    *(undefined4 *)(param_2 + 0x1438) = 0;
    *(undefined1 *)(param_2 + 0x143c) = 0;
  }
  bVar9 = (*(uint *)(param_2 + 0x17c) & 7) != 0;
  if (bVar9) {
    *(undefined1 *)(param_2 + 0x514) = 0;
  }
  else {
    *(undefined1 *)(param_2 + 0x514) = 7;
  }
  *(uint *)(param_2 + 0xadc) = (uint)!bVar9;
  _raw_spin_unlock_bh(param_1 + 0x285958);
  return 1;
}

