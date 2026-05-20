// module: mt7915.ko
// function: ba_reorder @ 0xa7ac4
// size: 3008 bytes
//

void ba_reorder(int param_1,int param_2,undefined4 param_3)

{
  undefined1 uVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  int iVar16;
  uint uVar17;
  int iVar18;
  int iVar19;
  undefined2 *local_44;
  undefined1 local_38;
  
  uVar2 = *(ushort *)(param_2 + 0x4e);
  uVar3 = *(ushort *)(param_2 + 0x24);
  uVar17 = (uint)uVar3;
  uVar5 = HcGetMaxStaNum();
  if (uVar2 < uVar5) {
    uVar5 = (uint)*(ushort *)
                   (param_1 + ((uint)*(ushort *)(param_2 + 0x4e) * 0xa60 +
                               (uint)*(byte *)(param_2 + 0x53) + 0x514f8) * 2 + 4);
    if (uVar5 == 0) {
      indicate_rx_pkt(param_1,param_2,param_3);
      *(int *)(param_1 + 0x9dcfc) = *(int *)(param_1 + 0x9dcfc) + 1;
      return;
    }
    iVar18 = param_1 + 0x1c0;
    iVar9 = param_1 + uVar5 * 0x60;
    iVar11 = iVar18 + uVar5 * 0x60;
    *(int *)(iVar9 + 0x210) = *(int *)(iVar9 + 0x210) + 1;
    if ((((*(uint *)(param_1 + 0x2f68c) & 1) != 0) && (iVar8 = *(int *)(iVar9 + 0x208), iVar8 != 0))
       && ((*(uint *)(param_1 + 0x2f68c) & 2) != 0)) {
      iVar9 = *(int *)(iVar9 + 0x20c) * 0x14;
      iVar6 = iVar8 + iVar9;
      *(ushort *)(iVar8 + iVar9) = uVar3;
      uVar1 = *(undefined1 *)(param_2 + 0x73);
      *(undefined1 *)(iVar6 + 3) = 0;
      *(undefined1 *)(iVar6 + 2) = uVar1;
      *(undefined2 *)(iVar6 + 4) = *(undefined2 *)(iVar11 + 0xc);
      *(undefined2 *)(iVar6 + 6) = *(undefined2 *)(param_2 + 0x4e);
      if ((*(uint *)(param_1 + 0x2f68c) & 4) != 0) {
        puVar14 = *(undefined4 **)(param_2 + 0x2c);
        *(undefined4 *)(iVar6 + 8) = *puVar14;
        *(undefined2 *)(iVar6 + 0xc) = *(undefined2 *)(puVar14 + 1);
        puVar14 = *(undefined4 **)(param_2 + 0x28);
        *(undefined4 *)(iVar6 + 0xe) = *puVar14;
        *(undefined2 *)(iVar6 + 0x12) = *(undefined2 *)(puVar14 + 1);
      }
      iVar9 = param_1 + uVar5 * 0x60;
      *(uint *)(iVar9 + 0x20c) = *(int *)(iVar9 + 0x20c) + 1U & 0xff;
    }
    uVar10 = jiffies;
    switch(*(undefined4 *)(param_1 + uVar5 * 0x60 + 0x1c8)) {
    case 0:
    case 1:
    case 2:
      FUN_000a4598(param_1,iVar18,iVar11);
      return;
    case 3:
      goto switchD_000a7c08_caseD_3;
    case 4:
      goto switchD_000a7c08_caseD_4;
    case 5:
      indicate_rx_pkt(param_1,param_2,param_3);
      return;
    default:
      uVar10 = 0x891;
      iVar9 = param_1 + uVar5 * 0x60;
      *(int *)(param_1 + 0x9dcec) = *(int *)(param_1 + 0x9dcec) + 1;
      *(int *)(iVar9 + 0x1e4) = *(int *)(iVar9 + 0x1e4) + 1;
      goto LAB_000a7e7c;
    }
  }
  uVar10 = 0x84e;
  *(int *)(param_1 + 0x9dce8) = *(int *)(param_1 + 0x9dce8) + 1;
LAB_000a7e7c:
  wlan_dbg_set_last_error(0,1,uVar10,"ba_reorder");
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
  return;
switchD_000a7c08_caseD_3:
  FUN_000a4598(param_1,iVar18,iVar11);
  iVar9 = param_1 + uVar5 * 0x60;
  if ((*(int *)(iVar9 + 500) != 0) || (*(int *)(iVar9 + 0x1ec) != 0)) {
    printk(&_LC72,0x87b);
    dump_stack();
  }
  if (3 < DebugLevel) {
    printk("%s:Reset Last Indicate Sequence(%d): amsdu state = %d\n","ba_reorder",
           *(undefined2 *)(param_2 + 0x24),*(undefined1 *)(param_2 + 0x73));
  }
  iVar9 = param_1 + uVar5 * 0x60;
  *(ushort *)(iVar18 + uVar5 * 0x60 + 0xc) = (ushort)((uVar17 - 1) * 0x100000 >> 0x14);
  *(undefined4 *)(iVar9 + 0x1d8) = uVar10;
  uVar1 = *(undefined1 *)(param_2 + 0x73);
  *(ushort *)(iVar9 + 0x1c2) = uVar3;
  *(undefined4 *)(iVar9 + 0x1c8) = 4;
  *(undefined1 *)(iVar9 + 0x1c1) = uVar1;
switchD_000a7c08_caseD_4:
  uVar10 = jiffies;
  iVar9 = param_1 + uVar5 * 0x60;
  if ((*(char *)(iVar9 + 0x1c0) == '\0') ||
     (iVar8 = FUN_000a4968(param_1,uVar17,*(undefined1 *)(param_2 + 0x73),iVar11,jiffies),
     iVar8 == 0)) {
    *(undefined1 *)(iVar9 + 0x1c0) = 1;
    if (*(byte *)(param_2 + 0x73) < 2) goto LAB_000a7f04;
  }
  else {
    *(int *)(param_1 + 0x9dd14) = *(int *)(param_1 + 0x9dd14) + 1;
    *(undefined1 *)(iVar9 + 0x1c0) = 1;
LAB_000a7f04:
    ba_flush_reordering_timeout_mpdus(param_1,iVar18,iVar11,uVar10);
  }
  iVar8 = uVar5 * 0x60;
  uVar12 = (uint)*(ushort *)(iVar18 + iVar8 + 0xc);
  if (uVar17 == (uVar12 + 1 & 0xfff)) {
LAB_000a7f88:
    local_44 = (undefined2 *)(iVar9 + 0x1c4);
    if ((*(uint *)(param_1 + 0x2f68c) & 0x80) != 0) {
      ba_resource_dump_all(param_1,1);
    }
    indicate_rx_pkt(param_1,param_2,param_3);
    if (*(byte *)(param_2 + 0x73) < 2) {
      iVar8 = iVar18 + uVar5 * 0x60;
      *(ushort *)(iVar8 + 0xc) = uVar3;
      iVar11 = FUN_000a4804(param_1,iVar18,iVar11,uVar17);
      if (iVar11 != 0xffff) {
        *(short *)(iVar8 + 0xc) = (short)iVar11;
      }
      *(undefined4 *)(param_1 + uVar5 * 0x60 + 0x1d8) = uVar10;
    }
    *local_44 = 0;
    goto LAB_000a7fc0;
  }
  if (uVar17 == uVar12) {
LAB_000a8004:
    local_44 = (undefined2 *)(iVar9 + 0x1c4);
    if (((*(uint *)(param_2 + 0x44) & 2) == 0) || (*(char *)(param_1 + 0x9daa3) != '\0')) {
      if ((*(uint *)(param_1 + 0x2f68c) & 0x40) != 0) {
        ba_resource_dump_all(param_1,1);
      }
      iVar11 = param_1 + uVar5 * 0x60;
      *(int *)(param_1 + 0x9dcf4) = *(int *)(param_1 + 0x9dcf4) + 1;
      *(int *)(iVar11 + 0x1dc) = *(int *)(iVar11 + 0x1dc) + 1;
      wlan_dbg_radio_statistics_inc(0,0xf);
      RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
    }
    else {
      *(undefined4 *)(param_1 + uVar5 * 0x60 + 0x1d8) = uVar10;
      indicate_rx_pkt(param_1,param_2,param_3);
    }
    *local_44 = 1;
    goto LAB_000a7fc0;
  }
  if ((uVar17 - uVar12 & 0x800) != 0) {
LAB_000a80b0:
    local_44 = (undefined2 *)(iVar9 + 0x1c4);
    if ((*(uint *)(param_1 + 0x2f68c) & 0x20) != 0) {
      ba_resource_dump_all(param_1,1);
    }
    iVar11 = param_1 + uVar5 * 0x60;
    *(int *)(param_1 + 0x9dcf0) = *(int *)(param_1 + 0x9dcf0) + 1;
    *(int *)(iVar11 + 0x1e0) = *(int *)(iVar11 + 0x1e0) + 1;
    wlan_dbg_radio_statistics_inc(0,0x10);
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
    *local_44 = 2;
    goto LAB_000a7fc0;
  }
  if ((uVar17 - (uVar12 + *(ushort *)(iVar18 + iVar8 + 0x14) + 1) & 0x800) == 0) {
    iVar6 = param_1 + iVar8;
    do {
      if ((*(uint *)(param_1 + 0x2f68c) & 0x10) != 0) {
        ba_resource_dump_all(param_1,1);
      }
      *(int *)(param_1 + 0x9dd04) = *(int *)(param_1 + 0x9dd04) + 1;
      iVar19 = iVar18 + iVar8;
      *(int *)(iVar6 + 0x1e8) = *(int *)(iVar6 + 0x1e8) + 1;
      iVar13 = uVar17 - *(ushort *)(iVar18 + iVar8 + 0x14);
      iVar16 = iVar13 + 1;
      if (iVar16 < 0) {
        iVar16 = iVar13 + 0x1001;
      }
      FUN_000a46ac(param_1,iVar18,iVar11,iVar16 - 1U & 0xfff);
      *(ushort *)(iVar19 + 0xc) = (ushort)((iVar16 - 1U) * 0x100000 >> 0x14);
      *(undefined4 *)(iVar6 + 0x1d8) = uVar10;
      iVar13 = FUN_000a4804(param_1,iVar18,iVar11,*(undefined2 *)(iVar19 + 0xc));
      if (iVar13 != 0xffff) {
        *(short *)(iVar19 + 0xc) = (short)iVar13;
      }
      *(undefined2 *)(iVar9 + 0x1c4) = 4;
      uVar12 = (uint)*(ushort *)(iVar18 + iVar8 + 0xc);
      if ((uVar12 + 1 & 0xfff) == uVar17) goto LAB_000a7f88;
      if (uVar17 == uVar12) goto LAB_000a8004;
      if ((uVar17 - uVar12 & 0x800) != 0) goto LAB_000a80b0;
    } while ((uVar17 - (uVar12 + *(ushort *)(iVar18 + iVar8 + 0x14) + 1) & 0x800) == 0);
  }
  local_44 = (undefined2 *)(iVar9 + 0x1c4);
  if ((*(uint *)(param_1 + 0x2f68c) & 8) != 0) {
    ba_resource_dump_all(param_1,1);
  }
  uVar2 = *(ushort *)(param_2 + 0x24);
  iVar8 = param_1 + uVar5 * 0x60;
  _raw_spin_lock_bh(iVar18 + (uint)*(byte *)(iVar8 + 0x1ff) * 0x14 + 0x2f408);
  uVar17 = (uint)*(byte *)(iVar8 + 0x1ff);
  if (iVar18 + uVar17 * 0x14 == -0x2f40c) {
    printk(&_LC1,0x46);
    dump_stack();
  }
  iVar8 = param_1 + uVar17 * 0x14;
  puVar14 = *(undefined4 **)(iVar8 + 0x2f5cc);
  if (puVar14 == (undefined4 *)0x0) {
    _raw_spin_unlock_bh(iVar18 + (uint)*(byte *)(param_1 + uVar5 * 0x60 + 0x1ff) * 0x14 + 0x2f408);
    if (1 < DebugLevel) {
      iVar8 = uVar5 * 0x60 + param_1;
      printk("!!! (used:%d/free:%d) Can\'t allocate reordering mpdu blk\n",
             *(undefined4 *)(iVar8 + 500),
             *(undefined4 *)((uint)*(byte *)(iVar8 + 0x1ff) * 0x14 + param_1 + 0x2f5d4));
    }
LAB_000a81f0:
    FUN_000a46ac(param_1,iVar18,iVar11,(uint)uVar2);
    iVar8 = iVar18 + uVar5 * 0x60;
    *(ushort *)(iVar8 + 0xc) = uVar2;
    indicate_rx_pkt(param_1,param_2,param_3);
    iVar11 = FUN_000a4804(param_1,iVar18,iVar11,*(undefined2 *)(iVar8 + 0xc));
    if (iVar11 != 0xffff) {
      *(short *)(iVar8 + 0xc) = (short)iVar11;
    }
    uVar10 = jiffies;
    iVar11 = param_1 + uVar5 * 0x60;
    *(undefined4 *)(iVar11 + 0x1f8) = 0;
    *(undefined4 *)(iVar11 + 0x1d8) = uVar10;
  }
  else {
    *(int *)(iVar8 + 0x2f5d4) = *(int *)(iVar8 + 0x2f5d4) + -1;
    *(undefined4 *)(iVar8 + 0x2f5cc) = *puVar14;
    __memzero(puVar14,0x1c);
    iVar8 = param_1 + uVar5 * 0x60;
    _raw_spin_unlock_bh(iVar18 + (uint)*(byte *)(iVar8 + 0x1ff) * 0x14 + 0x2f408);
    if ((*(uint *)(param_2 + 0x44) & 0x40) != 0) {
      FUN_000a4510(iVar18,iVar11,puVar14);
      goto LAB_000a81f0;
    }
    _raw_spin_lock_bh(iVar11 + 0x10);
    if (*(int *)(iVar8 + 500) < 1) {
      *(undefined4 *)(iVar8 + 0x1d8) = jiffies;
    }
    puVar14[5] = (uint)uVar2;
    *(undefined1 *)((int)puVar14 + 0x19) = *(undefined1 *)(param_2 + 0x4b);
    *(byte *)(puVar14 + 6) = (byte)*(undefined4 *)(param_2 + 0x44) & 2;
    if ((*(uint *)(param_2 + 0x44) & 0x40000) == 0) {
      convert_reordering_packet_to_preAMSDU_or_802_3_packet(param_1,param_2,param_3);
    }
    else {
      iVar8 = *(int *)(param_2 + 0x38);
      uVar10 = get_netdev_from_bssid(param_1,param_3);
      *(int *)(iVar8 + 0xc0) = *(int *)(iVar8 + 0xcc) + *(int *)(iVar8 + 100);
      *(undefined4 *)(iVar8 + 0x18) = uVar10;
    }
    local_38 = (undefined1)param_3;
    *(undefined1 *)(*(int *)(param_2 + 0x38) + 0x2d) = local_38;
    puVar14[4] = *(undefined4 *)(param_2 + 0x38);
    iVar8 = *(int *)(param_1 + uVar5 * 0x60 + 0x1f8);
    if (iVar8 == 0) {
      puVar15 = *(undefined4 **)(iVar11 + 0x2c);
      puVar7 = (undefined4 *)(iVar11 + 0x2c);
      if (puVar15 != (undefined4 *)0x0) {
        iVar8 = puVar15[5];
        iVar6 = puVar14[5];
        uVar17 = iVar8 - iVar6;
        puVar4 = puVar15;
        while ((uVar17 & 0x800) != 0) {
          puVar15 = (undefined4 *)*puVar4;
          puVar7 = puVar4;
          if (puVar15 == (undefined4 *)0x0) goto LAB_000a85c4;
          iVar8 = puVar15[5];
          puVar4 = puVar15;
          uVar17 = iVar8 - iVar6;
        }
        puVar15 = puVar4;
        if (iVar8 == iVar6) {
          iVar8 = uVar5 * 0x60 + param_1;
          *(int *)(param_1 + 0x9dcf8) = *(int *)(param_1 + 0x9dcf8) + 1;
          *(int *)(iVar8 + 0x1dc) = *(int *)(iVar8 + 0x1dc) + 1;
          wlan_dbg_set_last_error(0,1,0x809,"ba_enqueue_reordering_packet");
          RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
          FUN_000a4510(iVar18,iVar11,puVar14);
          *(undefined4 *)(iVar8 + 0x1f8) = 0;
          goto LAB_000a836c;
        }
      }
LAB_000a85c4:
      *puVar14 = puVar15;
      *puVar7 = puVar14;
      *(int *)(iVar11 + 0x34) = *(int *)(iVar11 + 0x34) + 1;
      *(undefined4 **)(param_1 + uVar5 * 0x60 + 0x1f8) = puVar14;
    }
    else {
      *(int *)(iVar8 + 0xc) = *(int *)(iVar8 + 0xc) + 1;
      *puVar14 = 0;
      if (*(undefined4 **)(iVar8 + 8) == (undefined4 *)0x0) {
        *(undefined4 **)(iVar8 + 4) = puVar14;
      }
      else {
        **(undefined4 **)(iVar8 + 8) = puVar14;
      }
      *(undefined4 **)(iVar8 + 8) = puVar14;
    }
LAB_000a836c:
    iVar8 = *(int *)(param_1 + uVar5 * 0x60 + 500);
    if ((iVar8 < 0) || ((int)(uint)*(ushort *)(iVar18 + uVar5 * 0x60 + 0x14) < iVar8)) {
      if (-1 < DebugLevel) {
        printk("!!! Something wrong !!! (qlen:%d, BAWinSize:%d)\n",iVar8,
               *(undefined2 *)(uVar5 * 0x60 + iVar18 + 0x14));
      }
      dump_ba_list(iVar18 + uVar5 * 0x60 + 0x2c);
    }
    _raw_spin_unlock_bh(iVar11 + 0x10);
  }
  *local_44 = 3;
LAB_000a7fc0:
  uVar1 = *(undefined1 *)(param_2 + 0x73);
  *(ushort *)(iVar9 + 0x1c2) = uVar3;
  *(undefined1 *)(iVar9 + 0x1c1) = uVar1;
  if (*(byte *)(param_2 + 0x73) < 2) {
    *(undefined4 *)(param_1 + uVar5 * 0x60 + 0x1f8) = 0;
  }
  return;
}

