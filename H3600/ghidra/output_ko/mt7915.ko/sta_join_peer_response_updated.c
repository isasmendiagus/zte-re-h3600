// module: mt7915.ko
// function: sta_join_peer_response_updated @ 0x76fa4
// size: 5168 bytes
//

undefined4
sta_join_peer_response_updated
          (int param_1,int param_2,void *param_3,int param_4,void *param_5,ushort param_6)

{
  byte bVar1;
  ushort uVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  undefined1 uVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  size_t sVar13;
  undefined4 uVar14;
  void *__dest;
  uint uVar15;
  uint extraout_r2;
  int iVar16;
  int iVar17;
  void *__s1;
  undefined4 uVar18;
  int iVar19;
  uint uVar20;
  uint uVar21;
  void *local_98;
  uint local_94;
  int local_88;
  uint local_74;
  int local_70;
  ushort local_58;
  ushort local_56;
  undefined2 local_54;
  undefined1 auStack_52 [4];
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  
  iVar8 = GetStaCfgByWdev();
  iVar9 = get_scan_tab_by_wdev(param_1,param_2);
  if (iVar8 == 0) {
    return 0;
  }
  iVar10 = GetAssociatedAPByWdev(param_1,param_2);
  if (iVar10 != 0) {
    iVar11 = memcmp((void *)(iVar10 + 0xec),(void *)((int)param_3 + 6),6);
    if (iVar11 == 0) {
      return 1;
    }
    MacTableDeleteEntry(param_1,*(undefined2 *)(iVar10 + 0xe0),(void *)(iVar10 + 0xec));
  }
  local_98 = (void *)((int)param_3 + 6);
  if (2 < DebugLevel) {
    printk("%s():receive desired BEACON,Channel=%d, (%d, %d)\n","sta_join_peer_response_updated",
           *(undefined1 *)((int)param_3 + 0x30),*(undefined2 *)((int)param_3 + 0x2e),
           *(undefined1 *)((int)param_3 + 0x38));
  }
  iVar10 = param_4 + 0x918;
  uVar6 = ConvertToRssi(param_1,iVar10,0);
  *(undefined1 *)(iVar8 + 0x2131c8) = uVar6;
  uVar6 = ConvertToRssi(param_1,iVar10,1);
  *(undefined1 *)(iVar8 + 0x2131c9) = uVar6;
  sVar7 = ConvertToRssi(param_1,iVar10,2);
  *(char *)(iVar8 + 0x2131cc) = *(char *)(iVar8 + 0x2131c8);
  *(char *)(iVar8 + 0x2131ca) = (char)sVar7;
  *(short *)(iVar8 + 0x2131d0) = (short)*(char *)(iVar8 + 0x2131c8) << 3;
  *(char *)(iVar8 + 0x2131ce) = (char)sVar7;
  *(char *)(iVar8 + 0x2131cd) = *(char *)(iVar8 + 0x2131c9);
  *(short *)(iVar8 + 0x2131d2) = (short)*(char *)(iVar8 + 0x2131c9) << 3;
  *(short *)(iVar8 + 0x2131d4) = sVar7 << 3;
  if (*(char *)(iVar8 + 0x4139) == '\0') {
    memmove((void *)(iVar8 + 0x4119),(void *)((int)param_3 + 0xc),
            (uint)*(byte *)((int)param_3 + 0x2c));
    *(undefined1 *)(iVar8 + 0x4139) = *(undefined1 *)((int)param_3 + 0x2c);
    local_94 = -1;
  }
  else {
    local_94 = BssSsidTableSearch(iVar9,local_98,iVar8 + 0x4119,*(char *)(iVar8 + 0x4139),
                                  *(undefined1 *)((int)param_3 + 0x30));
    if (local_94 == -1) {
      local_4e = *(undefined1 *)(param_4 + 0x918);
      local_4d = *(undefined1 *)(param_4 + 0x919);
      local_4c = *(undefined1 *)(param_4 + 0x91a);
      local_4b = *(undefined1 *)(param_4 + 0x91b);
      uVar18 = rtmp_avg_rssi(param_1,auStack_52);
      local_94 = BssTableSetEntry(param_1,iVar8,iVar9,param_3,uVar18,param_6,param_5);
      if (local_94 == -1) goto LAB_00077134;
      iVar10 = local_94 * 0xaf4;
      memmove((void *)(iVar9 + iVar10 + 0x4fe),(void *)(param_4 + 0x18),4);
      memmove((void *)(iVar9 + iVar10 + 0x502),(void *)(param_4 + 0x910),4);
      memmove((void *)(iVar9 + iVar10 + 0x506),(void *)(param_4 + 0x910),4);
      *(undefined2 *)((int)param_3 + 0x34) = *(undefined2 *)(iVar9 + iVar10 + 0x92);
      uVar21 = (uint)*(byte *)(param_4 + 0x91e) % 10;
      uVar6 = (undefined1)uVar21;
      if (uVar21 == 0) {
        uVar6 = 0xfb;
      }
      *(undefined1 *)(iVar9 + iVar10 + 0x8b) = uVar6;
      memmove((void *)(local_94 * 0xaf4 + iVar9 + 8),param_3,6);
    }
    else {
      if (*(int *)(param_2 + 0x12f4) == 0) {
        if (*(int *)(param_2 + 0x2c) == 1) {
          uVar21 = (uint)(*(int *)(param_2 + 0x174) != 1) << 4;
        }
        else {
          uVar21 = 0x10;
        }
        if (((uVar21 ^ *(ushort *)((int)param_3 + 0x34)) & 0x10) != 0) {
          if (2 < DebugLevel) {
            if (*(int *)(param_2 + 0x2c) == 1) {
              uVar18 = 0;
              if (*(int *)(param_2 + 0x174) != 1) {
                uVar18 = 1;
              }
            }
            else {
              uVar18 = 1;
            }
            printk("%s:AP privacy %d is differenct from STA privacy%d\n",
                   "sta_join_peer_response_updated",
                   ((uint)*(ushort *)((int)param_3 + 0x34) << 0x1b) >> 0x1f,uVar18);
          }
          ScanParmFill(param_1,auStack_52,iVar8 + 0x4119,*(undefined1 *)(iVar8 + 0x4139),2,0);
          cntl_scan_request(param_2,auStack_52);
          return 0;
        }
      }
      iVar10 = local_94 * 0xaf4 + iVar9;
      *(undefined2 *)((int)param_3 + 0x34) = *(undefined2 *)(iVar10 + 0x92);
      *(undefined1 *)(iVar8 + 0x2123f0) = *(undefined1 *)(iVar10 + 0xad4);
      *(undefined1 *)(iVar8 + 0x2123f1) = *(undefined1 *)(iVar10 + 0xad5);
    }
    iVar9 = local_94 * 0xaf4 + iVar9;
    *(undefined1 *)(iVar9 + 0x6ca) = 0;
    if (*(char *)((int)param_3 + 0x95) != '\0') {
      if (*(char *)((int)param_3 + 0x96) == '\0') {
        *(undefined1 *)(iVar8 + 0x2123e8) = 0;
      }
      else {
        *(undefined1 *)(iVar9 + 0x6ca) = 1;
        *(undefined1 *)(iVar8 + 0x2123e8) = 1;
      }
    }
  }
LAB_00077134:
  local_88 = iVar8 + 0x4119;
  *(ushort *)(iVar8 + 0x416c) = *(ushort *)((int)param_3 + 0x34) & 0x533;
  __dest = (void *)(iVar8 + 0x413a);
  *(undefined1 *)(iVar8 + 0x4118) = *(undefined1 *)((int)param_3 + 0x2d);
  sVar7 = *(short *)((int)param_3 + 0x2e);
  *(short *)(iVar8 + 0x416e) = sVar7;
  *(undefined1 *)(iVar8 + 0x4168) = *(undefined1 *)((int)param_3 + 0x38);
  memmove(__dest,local_98,6);
  if (sVar7 == 0) {
    *(undefined2 *)(iVar8 + 0x416e) = 100;
  }
  *(undefined1 *)(iVar8 + 0x4165) = *(undefined1 *)((int)param_3 + 0x30);
  *(undefined2 *)(iVar8 + 0x4174) = *(undefined2 *)((int)param_3 + 0x32);
  *(ushort *)(iVar8 + 0x4172) = (ushort)*(byte *)((int)param_3 + 0x4a);
  *(undefined2 *)(iVar8 + 0x4170) = *(undefined2 *)((int)param_3 + 0x4b);
  memmove((void *)(iVar8 + 0x4214),(void *)((int)param_3 + 200),0x14);
  check_legacy_rates((int)param_3 + 0xac,iVar8 + 0x4176,param_2);
  __memzero((void *)(iVar8 + 0x40e2),0x10);
  *(undefined1 *)(iVar8 + 0x2123f2) = *(undefined1 *)((int)param_3 + 0x178);
  memmove((void *)(iVar8 + 0x41c0),(void *)((int)param_3 + 0x98),0xb);
  iVar9 = DebugLevel;
  *(undefined1 *)(iVar8 + 0x40f2) = 0;
  *(undefined1 *)(iVar8 + 0x40f3) = 0;
  if (2 < iVar9) {
    printk("MlmeAux.ExtCapInfo=%d\n",*(byte *)(iVar8 + 0x41c0) & 1);
  }
  if (*(char *)(param_1 + 0x79564e) == '\x01') {
    *(byte *)(param_1 + 0x795643) = *(byte *)(param_1 + 0x795643) | 1;
  }
  *(undefined1 *)(iVar8 + 0x41cb) = *(undefined1 *)((int)param_3 + 0xa3);
  if ((*(uint *)((int)param_3 + 0xa8) & 1) == 0) {
    bVar1 = *(byte *)((int)param_3 + 0x30);
    RTMPZeroMemory(iVar8 + 0x4190,0x1a);
  }
  else {
    *(uint *)(iVar8 + 0x2123ec) = *(uint *)(iVar8 + 0x2123ec) | 1;
    bVar1 = *(byte *)((int)param_3 + 0x30);
    RTMPZeroMemory(iVar8 + 0x4190,0x1a);
  }
  local_70 = iVar8 + 0x4190;
  local_74 = (uint)bVar1;
  uVar21 = 0;
  iVar9 = MacTableInsertEntry(param_1,local_98,iVar8,1,0,1);
  if (iVar9 == 0) {
    printk(&_LC4,0x4ab);
    dump_stack();
    local_94 = 0;
  }
  else {
    uVar2 = *(ushort *)((int)param_3 + 0x34);
    local_58 = 0;
    *(undefined2 *)(iVar8 + 0x211f98) = 0;
    uVar20 = -((int)((uint)uVar2 << 0x1b) >> 0x1f);
    local_56 = local_58;
    __memzero((void *)(iVar8 + 0x211f9a),0x400);
    if ((*(int *)(param_2 + 0x12e4) == 0) || (*(char *)(param_2 + 0x3cc8) == '\0')) {
      if (*(uint *)(param_2 + 0x2c) == 1) {
        uVar21 = *(uint *)(param_2 + 0x174);
        if ((uVar21 != 1) && (uVar20 == 0)) goto LAB_00077908;
      }
      else {
        if (uVar20 == 0) {
LAB_00077908:
          if (DebugLevel < 0) {
            return 0;
          }
          printk("ERROR: The RSN IE of this received Probe-resp is dis-match : Peer no SEC\n");
          return 0;
        }
        if ((*(uint *)(param_2 + 0x2c) & 1) == 0) goto LAB_00077334;
        uVar21 = *(uint *)(param_2 + 0x174);
      }
      if ((uVar21 & uVar20) != 0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("ERROR: The RSN IE of this received Probe-resp is dis-match : wdev Config no SEC\n");
        return 0;
      }
    }
LAB_00077334:
    uVar21 = iVar9 + 0x2c4;
    PaserSecurityIE(param_3,&param_6,param_5,iVar9 + 0x17c,uVar21,iVar9 + 0x3a4,iVar9 + 0x563,
                    &local_58,&local_56);
    if (*(int *)(iVar9 + 0x17c) != 0) {
      uVar20 = 0;
    }
    if (uVar20 != 0) {
      uVar20 = *(uint *)(param_2 + 0x2c);
      if ((uVar20 & 4) == 0) {
        if (((uVar20 & 1) == 0) && ((uVar20 & 2) != 0)) {
          *(undefined4 *)(iVar9 + 0x17c) = 2;
        }
        else {
          *(undefined4 *)(iVar9 + 0x17c) = 1;
        }
      }
      else {
        *(undefined4 *)(iVar9 + 0x17c) = 4;
      }
      *(uint *)(iVar9 + 0x2c4) = *(uint *)(iVar9 + 0x2c4) | 0xe;
      *(uint *)(iVar9 + 0x3a4) = *(uint *)(iVar9 + 0x3a4) | 0xe;
    }
    *(undefined4 *)(iVar8 + 0x2124d4) = 0;
    *(undefined4 *)(iVar8 + 0x2124cc) = 0;
    *(undefined4 *)(iVar8 + 0x2124d0) = 0;
    *(undefined4 *)(iVar8 + 0x2124cc) = *(undefined4 *)(param_2 + 0x174);
    *(undefined4 *)(iVar8 + 0x2124d0) = *(undefined4 *)(param_2 + 0x254);
    *(undefined4 *)(iVar8 + 0x2124d4) = *(undefined4 *)(param_2 + 0x2c);
    *(undefined1 *)(iVar9 + 0x514) = 0;
    *(undefined1 *)(iVar9 + 0x515) = 0;
    os_zero_mem(iVar9 + 0x50c,8);
    if (((*(uint *)(param_2 + 0x2c) & 0x2000) == 0) || (*(uint *)(iVar9 + 0x17c) != 0x80)) {
      uVar20 = *(uint *)(iVar9 + 0x17c) & *(uint *)(param_2 + 0x2c);
      *(uint *)(iVar9 + 0x17c) = uVar20;
      uVar15 = *(uint *)(iVar9 + 0x2c4) & *(uint *)(param_2 + 0x174);
      *(uint *)(iVar9 + 0x2c4) = uVar15;
      if ((uVar20 == 0) || (uVar15 == 0)) goto LAB_00077418;
LAB_00077438:
      uVar15 = (*(uint *)(param_2 + 0x2c) << 0x12) >> 0x1f;
      if (uVar20 != 0x80) {
        uVar15 = 0;
      }
      if (uVar15 != 0) goto LAB_00077e18;
      if ((*(uint *)(iVar9 + 0x17c) & 0x48) == 0x48) {
        *(undefined4 *)(iVar9 + 0x17c) = 0x40;
      }
      else if ((*(uint *)(iVar9 + 0x17c) & 0x90) == 0x90) {
        *(undefined4 *)(iVar9 + 0x17c) = 0x80;
      }
      else if ((*(uint *)(param_2 + 0x2c) & 0x2080) == 0x2080) {
        *(undefined4 *)(iVar9 + 0x17c) = 0x2000;
      }
LAB_00077490:
      iVar10 = DebugLevel;
      if ((*(uint *)(iVar9 + 0x2c4) & 0x30) == 0x30) {
LAB_00077e38:
        iVar10 = DebugLevel;
        *(undefined4 *)(iVar9 + 0x2c4) = 0x20;
      }
      if (0 < iVar10) {
        uVar18 = GetAuthModeStr(*(undefined4 *)(iVar9 + 0x17c));
        uVar14 = GetEncryModeStr(*(undefined4 *)(iVar9 + 0x2c4));
        uVar21 = GetEncryModeStr(*(undefined4 *)(iVar9 + 0x3a4));
        printk("%s(): Candidate Security AKMMap=%s, PairwiseCipher=%s, GroupCipher=%s\n",
               "sta_join_peer_response_updated",uVar18,uVar14,uVar21);
      }
    }
    else {
      uVar20 = 0x80;
      uVar15 = 0;
      if (*(int *)(iVar9 + 0x2c4) == 0) {
LAB_00077418:
        if ((*(int *)(param_2 + 0x12e4) == 0) || (*(char *)(param_2 + 0x3cc8) == '\0')) {
          if (DebugLevel < 3) {
            return 0;
          }
          printk("%s, %u pEntry_Sec AKM %x Ciper %x, return due to desired BSS sec not mach\n",
                 "sta_join_peer_response_updated",0x50c,uVar20,uVar15);
          return 0;
        }
        goto LAB_00077438;
      }
LAB_00077e18:
      if (0 < DebugLevel) {
        printk("WPA3PSK STA connecting to WPA2PSK AP\n");
        goto LAB_00077490;
      }
      if ((*(uint *)(iVar9 + 0x2c4) & 0x30) == 0x30) goto LAB_00077e38;
    }
    if ((*(int *)(param_2 + 0x12e4) == 0) || (*(char *)(param_2 + 0x3cc8) == '\0')) {
      bVar5 = (byte)local_58;
      iVar11 = -((int)((uint)(byte)local_58 << 0x18) >> 0x1f);
      iVar19 = (uint)(byte)local_58 << 0x19;
      iVar10 = iVar19 >> 0x1f;
      iVar16 = -iVar10;
      bVar1 = (byte)local_58 >> 7;
      local_54 = local_58;
      if (local_94 != -1) {
        iVar12 = get_scan_tab_by_wdev(param_1,param_2);
        iVar17 = local_94 * 0xaf4;
        *(undefined2 *)(iVar8 + 0x2123d4) = 0;
        *(undefined1 *)(iVar8 + 0x2123d6) = 0;
        if (iVar12 + iVar17 + 8 != 0) {
          memmove((void *)(iVar8 + 0x2123d4),(void *)(iVar12 + iVar17 + 0xd8),2);
          *(undefined1 *)(iVar8 + 0x2123d6) = *(undefined1 *)(iVar12 + iVar17 + 0x4fc);
        }
      }
      cVar3 = (char)bVar5 >> 7;
      cVar4 = (char)(iVar19 >> 0x1f);
      if ((*(uint *)(param_2 + 0x2c) & 0x812000) == 0) {
        if (*(char *)(param_2 + 0x40e) != '\0') goto LAB_00077a70;
      }
      else {
        *(undefined1 *)(param_2 + 0x40c) = 1;
        *(undefined1 *)(param_2 + 0x40e) = 1;
LAB_00077a70:
        local_54 = CONCAT11(local_54._1_1_,(byte)local_54 & 0x3f | cVar4 * -0x40 | cVar3 * -0x80);
        if (iVar11 == 0) goto LAB_00077a94;
      }
      if (*(char *)(param_2 + 0x40c) == '\0') {
        local_54 = CONCAT11(local_54._1_1_,
                            ((byte)local_54 & 0xbf | cVar4 * -0x40) & 0x7f | cVar3 * -0x80);
        if (iVar16 != 0) {
LAB_00077a94:
          if (DebugLevel < 4) {
            return 0;
          }
          printk("%s: PMF fail: peer MFPR = %d, MFPC = %d\n","sta_join_peer_response_updated",iVar16
                 ,iVar11,uVar21);
          return 0;
        }
        goto LAB_000774d0;
      }
      iVar10 = iVar10 * -0x40;
      local_54 = CONCAT11(local_54._1_1_,(byte)local_54 & 0x3f | (byte)iVar10 | cVar3 * -0x80);
      if (iVar11 == 0) goto LAB_000774d0;
      *(undefined1 *)(iVar9 + 0x562) = 1;
      if ((*(uint *)(iVar9 + 0x17c) & 0x30000) == 0) {
        if (((local_56 != 0) || (iVar10 != 0)) || ((*(uint *)(iVar9 + 0x17c) & 0xef00) != 0)) {
          *(undefined1 *)(iVar9 + 0x400) = 1;
        }
      }
      else {
        *(undefined1 *)(iVar9 + 0x400) = 2;
      }
      uVar20 = *(uint *)(iVar9 + 0x17c);
      *(byte *)(iVar9 + 0x55c) = bVar1;
      *(undefined1 *)(iVar9 + 0x55e) = *(undefined1 *)(param_2 + 0x40e);
      if ((uVar20 & 0x2000) != 0) {
        *(undefined1 *)(iVar9 + 0x55e) = 1;
      }
    }
    else {
LAB_000774d0:
      uVar20 = *(uint *)(iVar9 + 0x17c);
    }
    if ((((uVar20 & 1) == 0) || ((*(uint *)(iVar9 + 0x2c4) & 1) == 0)) &&
       (((*(uint *)(iVar9 + 0x2c4) & 0x1e) != 0 && (*(char *)(param_1 + 0x795984) != '\0')))) {
LAB_00077504:
      local_94 = 0;
    }
    else {
      local_94 = 1;
      if (*(char *)(iVar8 + 0x4060) != '\x01') {
        if (*(char *)(iVar8 + 0x4060) != '\0') goto LAB_00077504;
        local_94 = (uint)(*(char *)(iVar8 + 0x40ac) == '\x01');
      }
    }
    if ((*(uint *)(iVar9 + 0x2c4) & 0xe) == 0) {
      sVar13 = strlen((char *)(param_2 + 0x179));
      uVar21 = (uint)*(byte *)(iVar8 + 0x4139);
      SetWPAPSKKey(param_1,(char *)(param_2 + 0x179),sVar13,local_88,uVar21,iVar9 + 0x30a);
      os_move_mem((void *)(iVar9 + 0x4a0),(void *)(iVar9 + 0xec),6);
      os_move_mem((void *)(iVar9 + 0x4a6),(void *)(param_2 + 0x1b),6);
    }
    else {
      os_move_mem((void *)(iVar9 + 0x180),(void *)(param_2 + 0x30),0x144);
      *(undefined1 *)(param_2 + 600) = *(undefined1 *)(param_2 + 0x178);
      *(undefined1 *)(iVar9 + 0x2c8) = *(undefined1 *)(param_2 + 0x178);
    }
    iVar10 = DebugLevel;
    *(undefined1 *)(iVar9 + 0x3a8) = *(undefined1 *)(param_2 + 600);
    if (2 < iVar10) {
      uVar21 = *(uint *)(iVar9 + 0x3a4);
      uVar20 = local_94;
      printk("%s(): Final Security AKM = 0x%x, PairwiseCipher = 0x%x, GroupCipher = 0x%x, bAllowNrate=%d\n"
             ,"sta_join_peer_response_updated",*(undefined4 *)(iVar9 + 0x17c),
             *(undefined4 *)(iVar9 + 0x2c4),uVar21,local_94);
      if (2 < DebugLevel) {
        printk("%s(): pEntry_SecConfig->PairwiseKeyId=%d, pEntry_SecConfig->GroupKeyId=%d\n",
               "sta_join_peer_response_updated",*(undefined1 *)(iVar9 + 0x2c8),
               *(undefined1 *)(iVar9 + 0x3a8),uVar21,uVar20);
      }
    }
    if (*(char *)(iVar9 + 0x562) == '\0') {
LAB_00077ad0:
      if ((*(char *)(iVar9 + 0x400) == '\x01') && (2 < DebugLevel)) {
        printk("[PMF] Use SHA256\n");
      }
    }
    else if (2 < DebugLevel) {
      printk("[PMF] Use PMF Connect\n");
      goto LAB_00077ad0;
    }
    *(ushort *)(iVar8 + 0x211f98) = param_6;
    memmove((void *)(iVar8 + 0x211f9a),param_5,(uint)param_6);
  }
  __memzero(iVar8 + 0x4108,0x10);
  if ((*(uint *)((int)param_3 + 0xa8) & 0x81) == 0) {
    *(undefined1 *)(iVar8 + 0x4167) = *(undefined1 *)(iVar8 + 0x4165);
LAB_000775cc:
    *(undefined1 *)(iVar8 + 0x40e0) = 0;
    *(undefined1 *)(iVar8 + 0x40f2) = 0;
    *(undefined1 *)(iVar8 + 0x40f3) = 0;
    *(undefined1 *)(iVar8 + 0x41cb) = 0xff;
    *(uint *)(iVar8 + 0x2123ec) = *(uint *)(iVar8 + 0x2123ec) & 0xfffffffc;
    RTMPZeroMemory(local_70,0x1a);
    RTMPZeroMemory(iVar8 + 0x41aa,0x16);
  }
  else {
    if (*(char *)(param_2 + 0x891) == '\0') goto LAB_000775cc;
    if ((*(ushort *)(param_2 + 0x18) & 0x18) == 0) {
      local_94 = 0;
    }
    if (local_94 == 0) goto LAB_000775cc;
    RTMPMoveMemory(iVar8 + 0x41aa,(int)param_3 + 0xf6,0x16);
    memmove((void *)(iVar8 + 0x40e2),(void *)((int)param_3 + 0xdf),0x10);
    *(undefined1 *)(iVar8 + 0x41cb) = *(undefined1 *)((int)param_3 + 0xa3);
    *(uint *)(iVar8 + 0x2123ec) = *(uint *)(iVar8 + 0x2123ec) | 1;
    *(undefined1 *)(iVar8 + 0x40e0) = 1;
    if ((*(uint *)((int)param_3 + 0xa8) & 0x80) != 0) {
      *(undefined1 *)(iVar8 + 0x40e1) = 1;
    }
    if (2 < DebugLevel) {
      uVar21 = ((uint)*(byte *)((int)param_3 + 0xdc) << 0x1e) >> 0x1f;
      printk("%s():(MpduDensity=%d, MaxRAmpduFactor=%d, BW=%d)\n","sta_join_peer_response_updated",
             ((uint)*(byte *)(iVar8 + 0x40fe) << 0x1b) >> 0x1d,*(byte *)(iVar8 + 0x40fe) & 3,uVar21)
      ;
    }
    if (((*(uint *)((int)param_3 + 0xa8) & 2) != 0) &&
       (local_74 = get_cent_ch_by_htinfo(param_1,(int)param_3 + 0xf6,(int)param_3 + 0xdc),
       0 < DebugLevel)) {
      printk("%s(): HT-CtrlChannel=%d, CentralChannel=>%d\n","sta_join_peer_response_updated",
             *(undefined1 *)((int)param_3 + 0xf6),local_74,uVar21);
    }
    if ((((*(ushort *)(param_2 + 0x18) & 0x20) != 0) && (0xe < *(byte *)(iVar8 + 0x4165))) &&
       ((*(uint *)((int)param_3 + 0xa8) & 4) != 0)) {
      uVar18 = wlan_config_get_vht_bw(param_2);
      local_54 = 0;
      memmove((void *)(iVar8 + 0x41cc),(void *)((int)param_3 + 0x10c),0xc);
      *(uint *)(iVar8 + 0x2123ec) = *(uint *)(iVar8 + 0x2123ec) | 4;
      *(undefined1 *)(iVar8 + 0x40f2) = 1;
      update_vht_op_info(uVar18,(int)param_3 + 0x118,&local_54);
      uVar20 = extraout_r2;
      if ((byte)local_54 != '\0') {
        uVar20 = (uint)local_54._1_1_;
      }
      *(byte *)(iVar8 + 0x40f3) = (byte)local_54;
      if ((byte)local_54 != '\0') {
        local_74 = uVar20;
      }
      if (0 < DebugLevel) {
        printk("%s(): CentralChannel=>%d\n","sta_join_peer_response_updated",local_74);
      }
    }
  }
  iVar10 = DebugLevel;
  *(undefined1 *)(iVar8 + 0x4167) = (undefined1)local_74;
  if (0 < iVar10) {
    printk("%s(): Set CentralChannel=%d\n","sta_join_peer_response_updated",local_74,iVar10,uVar21);
  }
  if (iVar9 != 0) {
    RTMPCheckHt(param_1,*(undefined2 *)(iVar9 + 0xe0),(int)param_3 + 0xdc,(int)param_3 + 0xf6);
  }
  RTMPUpdateMlmeRate(param_1,param_2);
  if ((*(char *)(param_2 + 0x8d4) == '\0') && ((*(ushort *)(param_2 + 0x18) & 0x18) == 0)) {
    __memzero(iVar8 + 0x41e6,0x24);
    __memzero(iVar8 + 0x420a,8);
    __memzero(iVar8 + 0x41e0,5);
  }
  else {
    memmove((void *)(iVar8 + 0x41e6),(void *)((int)param_3 + 0x50),0x24);
    memmove((void *)(iVar8 + 0x420a),(void *)((int)param_3 + 0x74),8);
    memmove((void *)(iVar8 + 0x41e0),(void *)((int)param_3 + 0x7c),5);
  }
  if (2 < DebugLevel) {
    printk("%s(): - after JOIN, SupRateLen=%d, ExtRateLen=%d\n","sta_join_peer_response_updated",
           *(undefined1 *)(iVar8 + 0x4176),*(undefined1 *)(iVar8 + 0x4183));
  }
  if (*(char *)((int)param_3 + 0x3c) == -1) {
    *(undefined1 *)(param_1 + 0x794cd8) = *(undefined1 *)(param_1 + 0x795041);
  }
  else {
    ChangeToCellPowerLimit(param_1);
  }
  *(undefined1 *)(param_1 + 0x794cd9) = *(undefined1 *)(param_1 + 0x795042);
  if (*(char *)(iVar8 + 0x4060) == '\x01') {
    local_54 = local_54 & 0xff00;
    if ((*(int *)(param_2 + 0x12e4) != 0) && (*(char *)(param_2 + 0x3cc8) == '\x01')) {
      uVar21 = wlan_config_get_ext_cha(param_2);
      iVar9 = wlan_config_get_ht_bw(param_2);
      bVar1 = *(byte *)((int)param_3 + 0xf7);
      if ((iVar9 == 1) && (((bVar1 & 4) != 0 && ((bVar1 & 3) != uVar21)))) {
        set_extcha_for_wdev(param_1,param_2,(bVar1 & 3) == 1);
        return 0;
      }
    }
    AdjustChannelRelatedValue
              (param_1,&local_54,0,((uint)*(byte *)(iVar8 + 0x4190) << 0x1e) >> 0x1f,
               *(undefined1 *)(iVar8 + 0x4165),*(undefined1 *)(iVar8 + 0x4167),param_2);
  }
  __s1 = (void *)(iVar8 + 0x213303);
  iVar9 = memcmp(__s1,&ZERO_MAC_ADDR,6);
  if (iVar9 == 0) {
    __s1 = __dest;
  }
  iVar9 = memcmp(__s1,local_98,6);
  if (iVar9 == 0) {
    if ((*(char *)(iVar8 + 0x213390) != '\x01') && ((&DAT_003678fc)[param_1] != '\x01')) {
      uVar18 = 1;
      goto LAB_0007773c;
    }
    iVar9 = get_scan_tab_by_wdev(param_1,param_2);
    iVar10 = BssTableSearch(iVar9,__dest,*(undefined1 *)(iVar8 + 0x1a));
    if (iVar10 == -1) {
      if (DebugLevel < 0) {
        return 0;
      }
      uVar18 = 0;
      printk("%s[%d]Can not find BssEntry\n","sta_join_peer_response_updated",0x66a);
      goto LAB_0007773c;
    }
    iVar19 = iVar10 * 0xaf4;
    iVar11 = ApCliAutoConnectBWAdjust(param_1,iVar8,iVar9 + iVar19 + 8);
    if (DebugLevel < 0) {
LAB_00077f5c:
      if (iVar11 == 0) {
        return 0;
      }
    }
    else {
      printk("%s[%d]Bssidx:%lu\n","sta_join_peer_response_updated",0x658,iVar10);
      if (*(char *)(iVar9 + iVar19 + 0x9c) != '\0') {
        if (DebugLevel < 0) goto LAB_00077f5c;
        printk("Root AP SSID: %s\n",iVar9 + iVar19 + 0x9d);
      }
      if (iVar11 == 0) goto LAB_00077738;
    }
    if (iVar11 == 2) {
      if (-1 < DebugLevel) {
        printk("Switch to channel :%d\n",*(undefined1 *)(iVar10 * 0xaf4 + iVar9 + 0x14));
      }
      uVar18 = 1;
      rtmp_set_channel(param_1,iVar8,*(undefined1 *)(iVar10 * 0xaf4 + iVar9 + 0x14));
    }
    else {
      uVar18 = 1;
    }
  }
  else {
LAB_00077738:
    uVar18 = 0;
  }
LAB_0007773c:
  if (2 < DebugLevel) {
    printk(" %s, %u  isGoingToConnect %d\n","sta_join_peer_response_updated",0x674,uVar18);
    return uVar18;
  }
  return uVar18;
}

