// module: mt7915.ko
// function: LinkUp_Infra @ 0x7100c
// size: 3592 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void LinkUp_Infra(int param_1,int param_2,int param_3,void *param_4,byte param_5)

{
  undefined1 uVar1;
  byte bVar2;
  bool bVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined4 uVar13;
  uint uVar14;
  undefined4 *puVar15;
  undefined4 uVar16;
  char cVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 *puVar20;
  code *pcVar21;
  bool bVar22;
  bool bVar23;
  undefined1 local_b7;
  undefined4 local_b6;
  undefined2 local_b2;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined2 local_a4;
  undefined1 local_a2;
  byte local_a1;
  undefined1 auStack_a0 [114];
  undefined1 auStack_2e [10];
  
  local_b7 = 1;
  local_b2 = 0xffff;
  local_b6 = 0xffffffff;
  if (param_3 == 0 || param_2 == 0) {
    return;
  }
  iVar5 = GetStaCfgByWdev();
  uVar1 = *(undefined1 *)(param_2 + 0xe);
  if (iVar5 == 0) {
    printk(&_LC1,0x8eb);
    dump_stack();
    return;
  }
  if (*(int *)(param_2 + 0x14) == 0x100) {
    if (0 < DebugLevel) {
      printk("%s - !!! Rept CliIdx %d !!!\n","LinkUp_Infra",uVar1);
      goto LAB_00071080;
    }
    if (*(int *)(iVar5 + 0x12e4) != 0) goto LAB_00071474;
    *(undefined1 *)(iVar5 + 0x2124ba) = 0;
    *(undefined1 *)(iVar5 + 0x2124bb) = 0;
    bVar3 = true;
    *(undefined2 *)(iVar5 + 0x2124be) = *(undefined2 *)(param_3 + 0xe0);
    bVar23 = false;
  }
  else {
LAB_00071080:
    if (*(int *)(iVar5 + 0x12e4) == 0) {
      bVar3 = true;
      bVar23 = false;
    }
    else {
LAB_00071474:
      bVar23 = *(char *)(iVar5 + 0x3cc8) != '\0';
      bVar3 = !bVar23;
    }
    iVar6 = DebugLevel;
    *(undefined1 *)(iVar5 + 0x2124ba) = 0;
    *(undefined1 *)(iVar5 + 0x2124bb) = 0;
    *(undefined2 *)(iVar5 + 0x2124be) = *(undefined2 *)(param_3 + 0xe0);
    if (2 < iVar6) {
      printk("%s:BeaconPeriod(%d),DtimPeriod(%d)\n","LinkUp_Infra",*(undefined2 *)(iVar5 + 0x416e),
             *(undefined1 *)(iVar5 + 0x4168));
    }
  }
  puVar20 = (undefined4 *)(iVar5 + 0x212428);
  *(undefined4 *)(param_2 + 0x21) = *puVar20;
  *(undefined2 *)(param_2 + 0x25) = *(undefined2 *)(iVar5 + 0x21242c);
  uVar14 = (uint)*(ushort *)(param_3 + 0xe0);
  *(undefined1 *)(param_3 + 0x12f8) = *(undefined1 *)(iVar5 + 0x2123f2);
  if ((((*(uint *)(param_2 + 0x2c) & 1) != 0) && ((*(uint *)(param_2 + 0x174) & 1) != 0)) ||
     ((*(uint *)(param_2 + 0x174) & 0xe) != 0)) {
    *(undefined1 *)(param_2 + 0x888) = 1;
    *(undefined4 *)(iVar5 + 0x2124c4) = 0;
    WLAN_EXTENDER_Report_LinkUpDown_Event(param_1,param_2,0xa427);
    bVar2 = *(byte *)(param_3 + 0x12f8);
    if ((bVar2 & 8) == 0) {
      *(undefined4 *)(param_1 + 0xa7cc00) = 0xffffffff;
    }
    else if ((bVar2 & 7) != 0) {
      *(uint *)(param_1 + 0xa7cc00) = (bVar2 & 7) - 1;
    }
    if (-1 < DebugLevel) {
      printk("(%s): set max hopnum %d \n","LinkUp_Infra",*(undefined4 *)(param_1 + 0xa7cc00));
    }
  }
  bVar22 = bVar3;
  if ((*(uint *)(param_2 + 0x2c) & 0x12cf8) == 0) {
    bVar22 = false;
  }
  if (bVar22) {
    *(undefined1 *)(param_2 + 0x888) = 2;
    *(undefined4 *)(iVar5 + 0x2124c4) = 1;
  }
  _raw_spin_lock_bh(param_1 + 0x285958);
  *(undefined1 *)(param_1 + uVar14 * 0x620 + 0x2f762) = *(undefined1 *)(param_2 + 0x888);
  _raw_spin_unlock_bh(param_1 + 0x285958);
  iVar6 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if ((iVar6 == 2) && (*(char *)(iVar5 + 0x41e6) != '\0')) {
    *(undefined1 *)(param_3 + 0x13bc) = *(undefined1 *)(iVar5 + 0x4202);
    *(undefined1 *)(param_3 + 0x13bd) = *(undefined1 *)(iVar5 + 0x4203);
    *(undefined1 *)(param_3 + 0x13be) = *(undefined1 *)(iVar5 + 0x4204);
    *(undefined1 *)(param_3 + 0x13bf) = *(undefined1 *)(iVar5 + 0x4205);
  }
  if ((*(byte *)(param_1 + 0x286294) & 3) != 3) goto LAB_00071230;
  iVar6 = *(int *)(param_2 + 0x14);
  if (((&DAT_0036790d)[param_1] == '\0') || (iVar6 != 2)) {
LAB_0007170c:
    if ((iVar6 != 0x100) ||
       ((*(char *)(iVar5 + 0x3f59) != '\0' && (*(char *)(iVar5 + 0x2123e8) != '\0'))))
    goto LAB_00071804;
    iVar6 = *(int *)(param_2 + 4);
    piVar7 = (int *)MacTableLookup(param_1,(void *)(iVar6 + 0x7d));
    if ((piVar7 == (int *)0x0) || (*piVar7 != 0x20001)) {
      *(undefined1 *)(iVar6 + 3) = 1;
    }
    else {
      *(undefined1 *)(iVar6 + 3) = 4;
      piVar7[0x2c0] = iVar6;
    }
    *(undefined1 *)(iVar6 + 1) = 1;
    *(undefined4 *)(*(int *)(param_3 + 0xafc) + 0x4148) = 0;
    uVar4 = HcGetRepeaterOmac(param_2);
    *(undefined1 *)(param_1 + uVar14 * 0x620 + 0x2fa7d) = uVar4;
    if (((iVar6 != 0) && (bVar2 = *(byte *)(iVar6 + 3), (bVar2 & 1) != 0)) &&
       (iVar8 = memcmp(&DAT_00368118 + param_1,(void *)(iVar6 + 0x7d),6), iVar8 == 0)) {
      *(byte *)(iVar6 + 3) = bVar2 | 2;
    }
    *(undefined1 *)(iVar6 + 5) = 2;
  }
  else {
    pcVar21 = _release_firmware;
    if (_release_firmware != release_firmware) {
      do {
        if ((*(uint *)(pcVar21 + 0x108) & 2) != 0) {
          puVar15 = *(undefined4 **)(pcVar21 + 0x1a8);
          bVar22 = -1 < DebugLevel;
          *(undefined4 *)(&DAT_00368118 + param_1) = *puVar15;
          *(undefined2 *)(&DAT_0036811c + param_1) = *(undefined2 *)(puVar15 + 1);
          if (bVar22) {
            printk(" Bridge Addr = %02x:%02x:%02x:%02x:%02x:%02x. !!!\n",(&DAT_00368118)[param_1],
                   (&DAT_00368119)[param_1],(&DAT_0036811a)[param_1],(&DAT_0036811b)[param_1],
                   (&DAT_0036811c)[param_1],(&DAT_0036811d)[param_1]);
          }
        }
        iVar6 = RepeaterInvaildMacLookup(param_1,*(undefined4 *)(pcVar21 + 0x1a8));
        if (iVar6 == 0) {
          InsertIgnoreAsRepeaterEntryTable(param_1,*(undefined4 *)(pcVar21 + 0x1a8));
        }
        pcVar21 = *(code **)pcVar21;
      } while (pcVar21 != release_firmware);
      iVar6 = *(int *)(param_2 + 0x14);
      goto LAB_0007170c;
    }
LAB_00071804:
    *(undefined1 *)(iVar5 + 0x213336) = 1;
    *(undefined2 *)(iVar5 + 0x2132e0) = *(undefined2 *)(param_3 + 0xe0);
    *(undefined4 *)(param_2 + 0x21) = *(undefined4 *)(iVar5 + 0x413a);
    *(undefined2 *)(param_2 + 0x25) = *(undefined2 *)(iVar5 + 0x413e);
    os_move_mem((void *)(param_2 + 0x99a),(undefined4 *)(param_2 + 0x21),6);
    *(undefined4 *)(param_3 + 0xec) = *(undefined4 *)(iVar5 + 0x413a);
    *(undefined2 *)(param_3 + 0xf0) = *(undefined2 *)(iVar5 + 0x413e);
    *(byte *)(iVar5 + 0x212426) = *(byte *)(iVar5 + 0x4139);
    memmove((void *)(iVar5 + 0x212406),(void *)(iVar5 + 0x4119),(uint)*(byte *)(iVar5 + 0x4139));
    *(undefined4 *)(iVar5 + 0x213348) = jiffies;
  }
  if ((*(uint *)(param_3 + 0x2c4) & 0xe) == 0) {
    if ((bVar3) && ((*(uint *)(param_3 + 0x17c) & 0x2001) == 0)) {
      uVar10 = *(undefined4 *)(param_2 + 0x1be);
      uVar13 = *(undefined4 *)(param_2 + 0x1c2);
      uVar11 = *(undefined4 *)(param_2 + 0x1c6);
      *(undefined4 *)(param_3 + 0x30a) = *(undefined4 *)(param_2 + 0x1ba);
      *(undefined4 *)(param_3 + 0x312) = uVar13;
      *(undefined4 *)(param_3 + 0x316) = uVar11;
      *(undefined4 *)(param_3 + 0x30e) = uVar10;
      uVar10 = *(undefined4 *)(param_2 + 0x1ce);
      uVar13 = *(undefined4 *)(param_2 + 0x1d2);
      uVar11 = *(undefined4 *)(param_2 + 0x1d6);
      *(undefined4 *)(param_3 + 0x31a) = *(undefined4 *)(param_2 + 0x1ca);
      *(undefined4 *)(param_3 + 0x322) = uVar13;
      *(undefined4 *)(param_3 + 0x31e) = uVar10;
      *(undefined4 *)(param_3 + 0x326) = uVar11;
    }
    os_move_mem((void *)(param_3 + 0x4a0),(void *)(param_3 + 0xec),6);
    os_move_mem((void *)(param_3 + 0x4a6),(void *)(param_2 + 0x1b),6);
    os_zero_mem(param_3 + 0x50c,8);
    *(undefined1 *)(param_3 + 0x514) = 7;
  }
  else {
    os_move_mem((void *)(param_3 + 0x180),(void *)(param_2 + 0x30),0x144);
    *(undefined1 *)(param_2 + 600) = *(undefined1 *)(param_2 + 0x178);
    *(undefined1 *)(param_3 + 0x2c8) = *(undefined1 *)(param_2 + 0x178);
  }
  iVar6 = DebugLevel;
  *(undefined1 *)(param_3 + 0x3a8) = *(undefined1 *)(param_2 + 600);
  if (2 < iVar6) {
    uVar18 = *(undefined4 *)(param_3 + 0x17c);
    uVar13 = GetAuthModeStr(uVar18);
    uVar19 = *(undefined4 *)(param_3 + 0x2c4);
    uVar10 = GetEncryModeStr(uVar19);
    uVar16 = *(undefined4 *)(param_3 + 0x3a4);
    uVar11 = GetEncryModeStr(uVar16);
    printk("%s: (apcli%d) connect AKM(0x%x)=%s, PairwiseCipher(0x%x)=%s, GroupCipher(0x%x)=%s\n",
           "LinkUp_Infra",uVar1,uVar18,uVar13,uVar19,uVar10,uVar16,uVar11);
    if (2 < DebugLevel) {
      printk("%s(): PairwiseKeyId=%d, GroupKeyId=%d\n","LinkUp_Infra",
             *(undefined1 *)(param_3 + 0x2c8),*(undefined1 *)(param_3 + 0x3a8),uVar13,uVar19,uVar10,
             uVar16,uVar11);
    }
  }
  iVar6 = *(int *)(param_2 + 0x14);
  if (iVar6 == 2) {
    if (*(char *)(param_1 + uVar14 * 0x620 + 0x2f762) == '\x01') {
      MWDSAPCliPeerEnable(param_1,iVar5,param_3);
      iVar6 = *(int *)(param_2 + 0x14);
      goto LAB_0007192c;
    }
  }
  else {
LAB_0007192c:
    if (iVar6 == 0x100) {
      AsicInsertRepeaterRootEntry
                (param_1,*(undefined2 *)(param_3 + 0xe0),iVar5 + 0x413a,
                 *(undefined1 *)(param_2 + 0xe));
    }
  }
  (&DAT_003678f8)[param_1] = (&DAT_003678f8)[param_1] + '\x01';
  cVar17 = *(char *)(iVar5 + 0x213390);
  if (cVar17 == '\0') {
    uVar9 = wlan_config_get_ext_cha(param_2);
    iVar6 = get_scan_tab_by_wdev(param_1,param_2);
    iVar8 = BssTableSearch(iVar6,param_3 + 0xae0,*(undefined1 *)(param_2 + 0x1a));
    if (iVar8 == -1) {
      if (-1 < DebugLevel) {
        printk("%s[%d] ERROR! can\'t find link up BSS, use config BW setting instead\n",
               "LinkUp_Infra",0xa3b);
      }
    }
    else {
      uVar9 = *(byte *)(iVar8 * 0xaf4 + iVar6 + 0x58) & 3;
    }
    uVar12 = ((uint)*(ushort *)(param_3 + 0xbe) << 0x17) >> 0x1e;
    if (uVar12 < 2) {
      wlan_operate_set_ht_bw(param_2,uVar12,uVar9);
      cVar17 = *(char *)(iVar5 + 0x213390);
    }
    else {
      if (uVar12 == 3) {
        uVar13 = 2;
      }
      else {
        uVar13 = 1;
      }
      wlan_operate_set_vht_bw(param_2,uVar13);
      wlan_operate_set_ht_bw(param_2,1,uVar9);
      cVar17 = *(char *)(iVar5 + 0x213390);
    }
  }
  if (((cVar17 == '\x01') && (*(int *)(param_2 + 0x14) == 2)) &&
     (*(char *)(param_1 + uVar14 * 0x620 + 0x2f762) == '\x01')) {
    if (2 < DebugLevel) {
      printk("ApCli auto connected: ApCliLinkUp()\n");
    }
    *(undefined1 *)(iVar5 + 0x213390) = 0;
  }
  *(undefined1 *)(iVar5 + 0x213336) = 1;
LAB_00071230:
  if (((*(int *)(param_2 + 0x14) == 2) && (iVar6 = wdev_do_linkup(param_2,param_3), iVar6 != 1)) &&
     (0 < DebugLevel)) {
    printk("%s(): linkup fail!!\n","LinkUp_Infra");
  }
  iVar6 = wdev_do_conn_act(iVar5,param_3);
  if ((iVar6 != 1) && (0 < DebugLevel)) {
    printk("%s(): connect fail!!\n","LinkUp_Infra");
  }
  if ((*(char *)(iVar5 + 0x212426) != *(char *)(iVar5 + 0x212427)) ||
     (iVar6 = RTMPCompareMemory(iVar5 + 0x21242e,iVar5 + 0x212406), iVar6 != 0)) {
    RTMP_IndicateMediaState(param_1,0);
    iVar6 = DebugLevel;
    *(undefined4 *)(param_1 + 0xa39fa4) = 1;
    if (2 < iVar6) {
      printk("NDIS_STATUS_MEDIA_DISCONNECT Event AA!\n");
    }
  }
  ComposePsPoll(param_1,"BssEntrySet" + param_1 + 5,*(undefined2 *)(iVar5 + 0x40b0),puVar20,
                iVar5 + 0x1b);
  ComposeNullFrame(param_1,"BssTableSetEntry" + param_1 + 9,puVar20,iVar5 + 0x1b,puVar20);
  AsicSetSyncModeAndEnable(param_1,*(undefined2 *)(&DAT_00794c50 + param_1),0,0);
  MacTableSetEntryRaCap(param_1,param_3,iVar5 + 0x4214);
  if ((*(uint *)(iVar5 + 0x2123ec) & 4) != 0) {
    MacTableEntryCheck2GVHT(param_1,param_3);
  }
  iVar6 = param_1 + (uint)*(ushort *)(param_3 + 0xe0) * 0x620;
  *(undefined4 *)(iVar6 + 0x2f75a) = *(undefined4 *)(param_2 + 0x21);
  *(undefined2 *)(iVar6 + 0x2f75e) = *(undefined2 *)(param_2 + 0x25);
  if ((*(uint *)(param_2 + 0x174) & 0xe) != 0) {
    memset(&local_b0,0,0x88);
    os_zero_mem(&local_b0,0x88);
    local_a2 = *(undefined1 *)(param_2 + 0xc);
    local_a8 = *(undefined4 *)(param_3 + 0x3a4);
    local_a4 = *(undefined2 *)(param_2 + 0x9a0);
    local_a1 = *(byte *)(param_3 + 0x3a8);
    local_ac = 1;
    local_b0 = 2;
    os_move_mem(auStack_2e,&local_b6,6);
    os_move_mem(auStack_a0,(void *)(param_3 + 0x17c + (uint)local_a1 * 0x51 + 4),0x51);
    HW_ADDREMOVE_KEYTABLE(param_1,&local_b0);
    os_zero_mem(&local_b0,0x88);
    local_a4 = *(undefined2 *)(param_3 + 0xe0);
    local_a2 = *(undefined1 *)(param_2 + 0xc);
    local_a1 = *(byte *)(param_3 + 0x2c8);
    local_a8 = *(undefined4 *)(param_3 + 0x2c4);
    local_ac = 2;
    local_b0 = 0;
    os_move_mem(auStack_2e,(void *)(param_3 + 0xec),6);
    os_move_mem(auStack_a0,(void *)(param_3 + 0x17c + (uint)local_a1 * 0x51 + 4),0x51);
    HW_ADDREMOVE_KEYTABLE(param_1,&local_b0);
  }
  if ((*(uint *)(param_2 + 0x2c) & 7) == 0) {
    if ((*(uint *)(param_2 + 0x2c) & 0x90) != 0) {
      if (((*(byte *)(param_1 + 0x286294) & 3) != 3) || (*(int *)(param_2 + 0x14) != 2)) {
        RTMPSetTimer(iVar5 + 0x212470,20000);
      }
      if (*(char *)(param_2 + 0x3b58) != '\0') {
        RTMPSetTimer(param_2 + 0x3b5c,10000);
      }
    }
  }
  else {
    *(undefined4 *)(param_1 + 0xa39fa4) = 0;
    RTMP_IndicateMediaState(param_1,1);
  }
  if (2 < DebugLevel) {
    printk("!!! LINK UP !!!  ClientStatusFlags=%lx)\n",*(undefined4 *)(param_3 + 0xb4));
  }
  if (bVar23) {
    RTMPCancelTimer(iVar5 + 0x212470,&local_b7);
    *(undefined4 *)(param_2 + 0x12f4) = 5;
    *(undefined4 *)(param_2 + 0x12f0) = 5;
    __memzero((void *)(iVar5 + 0x212406),0x20);
    memmove((void *)(iVar5 + 0x212406),param_4,(uint)param_5);
    *(byte *)(iVar5 + 0x212426) = param_5;
  }
  else {
    _WscStop(param_1,1,param_2 + 0x12e4,0);
  }
  MlmeUpdateTxRatesWdev(param_1,1,param_2);
  MlmeUpdateHtTxRates(param_1,param_2);
  if (2 < DebugLevel) {
    printk("!!! LINK UP !! (StaActive.bHtEnable =%d)\n",*(undefined1 *)(iVar5 + 0x40e0));
  }
  MlmeUpdateVhtTxRates(param_1,param_3,param_2);
  if (((*(uint *)(param_3 + 0xb4) & 4) != 0) && (AsicSetPiggyBack(param_1,1), 2 < DebugLevel)) {
    printk("Turn on Piggy-Back\n");
  }
  return;
}

