// module: mt7915.ko
// function: mt_ate_get_txlen_by_pkt_tx_time @ 0x284888
// size: 2368 bytes
//

uint mt_ate_get_txlen_by_pkt_tx_time(undefined4 param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int extraout_r1;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  byte *extraout_r12;
  byte *pbVar17;
  undefined *puVar18;
  uint local_34;
  uint local_30;
  
  iVar4 = net_ad_wrap_service();
  iVar13 = param_2 * 0xd18;
  iVar12 = *(int *)(iVar4 + iVar13 + 0x10f0);
  net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  uVar10 = (uint)*(byte *)(iVar4 + iVar13 + 0x1135);
  iVar4 = net_ad_wrap_service(param_1);
  bVar1 = *(byte *)(iVar4 + iVar13 + 0x1138);
  uVar9 = (uint)bVar1;
  iVar4 = net_ad_wrap_service(param_1);
  uVar16 = (uint)*(byte *)(iVar4 + iVar13 + 0x1136);
  iVar4 = net_ad_wrap_service(param_1);
  local_34 = (uint)*(byte *)(iVar4 + iVar13 + 0x113c);
  if (uVar10 == 0) {
    iVar4 = 0;
    do {
      iVar5 = iVar4 * 8;
      iVar13 = iVar4 * 8;
      iVar4 = iVar4 + 1;
      if ((byte)(&DAT_002a7398)[iVar5] == uVar9) {
        uVar11 = *(uint *)(&DAT_002a739c + iVar13);
        goto LAB_00284968;
      }
    } while (iVar4 != 7);
    uVar11 = 1000;
LAB_0028494c:
    iVar4 = net_ad_wrap_service(param_1);
    uVar9 = 0;
    *(undefined1 *)(param_2 * 0xd18 + iVar4 + 0x1138) = 0;
LAB_00284968:
    uVar14 = 1;
    local_30 = 1;
    uVar15 = (iVar12 * uVar11) / 8000;
    iVar4 = DebugLevel;
    uVar8 = uVar9;
  }
  else {
    if (uVar10 == 1) {
      iVar4 = 0;
      do {
        iVar5 = iVar4 * 8;
        iVar13 = iVar4 * 8;
        iVar4 = iVar4 + 1;
        if ((byte)(&DAT_002a73d0)[iVar5] == uVar9) {
          uVar11 = *(uint *)(&UNK_002a73d4 + iVar13);
          goto LAB_00284968;
        }
      } while (iVar4 != 8);
      uVar11 = 6000;
      goto LAB_0028494c;
    }
    uVar8 = uVar9;
    if (uVar10 - 2 < 2) {
      if (uVar9 == 0x20) {
        uVar14 = 1;
        local_30 = 1;
        uVar11 = uVar14;
      }
      else {
        local_30 = (bVar1 >> 3) + 1;
        uVar9 = uVar9 & 7;
        if (uVar16 == 1) {
          uVar14 = 2;
          uVar11 = local_30 * 2;
        }
        else {
          uVar14 = 1;
          uVar11 = local_30;
        }
      }
      iVar4 = 0;
      do {
        iVar5 = iVar4 * 8;
        iVar13 = iVar4 * 8;
        iVar4 = iVar4 + 1;
        if ((byte)(&DAT_002a7410)[iVar5] == uVar9) {
          iVar4 = *(int *)(&UNK_002a7414 + iVar13);
          goto LAB_00284bdc;
        }
      } while (iVar4 != 9);
      iVar4 = 0x1964;
      iVar13 = net_ad_wrap_service(param_1);
      uVar9 = 0;
      *(undefined1 *)(param_2 * 0xd18 + iVar13 + 0x1138) = 0;
      uVar8 = 0;
LAB_00284bdc:
      uVar11 = uVar11 * iVar4;
      if (local_34 == 1) {
        uVar11 = (uVar11 / 9) * 10;
      }
      uVar15 = (iVar12 * uVar11) / 8000;
      iVar4 = DebugLevel;
    }
    else if ((uVar10 & 0xf7) == 4) {
      if (uVar16 == 0) {
        uVar11 = 9;
        pbVar17 = &DAT_005e2440;
      }
      else if (uVar16 == 1) {
        uVar11 = 10;
        pbVar17 = (byte *)0x5e2528;
      }
      else if (uVar16 == 2) {
        uVar11 = 10;
        pbVar17 = (byte *)0x5e24d8;
      }
      else {
        pbVar17 = &DAT_005e2440;
        if (uVar16 == 3) {
          uVar11 = 10;
          pbVar17 = (byte *)0x5e2488;
        }
        else {
          uVar11 = 9;
        }
      }
      iVar4 = net_ad_wrap_service(param_1);
      bVar1 = *pbVar17;
      uVar8 = (uint)bVar1;
      local_30 = (uint)*(byte *)(param_2 * 0xd18 + iVar4 + 0x1139);
      uVar14 = 0;
      if (uVar8 == uVar9) {
LAB_00284c70:
        iVar13 = *(int *)(pbVar17 + uVar14 + 4);
        uVar8 = uVar9;
      }
      else {
        do {
          uVar14 = uVar14 + 1 & 0xff;
          if (uVar11 <= uVar14) break;
        } while (pbVar17[uVar14 * 8] != uVar9);
        if (uVar14 != uVar11) {
          uVar14 = uVar14 << 3;
          goto LAB_00284c70;
        }
        iVar13 = *(int *)(pbVar17 + 4);
        iVar4 = net_ad_wrap_service(param_1);
        *(byte *)(param_2 * 0xd18 + iVar4 + 0x1138) = bVar1;
      }
      uVar11 = local_30 * iVar13;
      if (local_34 == 1) {
        uVar11 = (uVar11 / 9) * 10;
      }
      uVar14 = 1;
      uVar15 = (iVar12 * uVar11) / 0x50;
      iVar4 = DebugLevel;
      uVar9 = uVar8;
    }
    else if (uVar10 == 8) {
      iVar4 = net_ad_wrap_service(param_1);
      switch(*(undefined1 *)(iVar4 + iVar13 + 0x113c)) {
      case 0:
      case 1:
      case 4:
        local_34 = 0;
        break;
      case 2:
        local_34 = 1;
        break;
      case 3:
        local_34 = 2;
      }
      iVar4 = net_ad_wrap_service(param_1);
      pbVar17 = extraout_r12;
      if (uVar16 == 0) {
        pbVar17 = &DAT_005e2280;
      }
      local_30 = (uint)*(byte *)(param_2 * 0xd18 + iVar4 + 0x1139);
      if (uVar16 != 0) {
        if (uVar16 == 1) {
          pbVar17 = &DAT_005e22f0;
        }
        else if (uVar16 == 2) {
          pbVar17 = &DAT_005e2360;
        }
        else {
          pbVar17 = &DAT_005e2280;
          if (uVar16 == 6 || uVar16 == 3) {
            pbVar17 = &DAT_005e23d0;
          }
        }
      }
      pbVar7 = pbVar17;
      do {
        if (*pbVar7 == uVar9) {
          iVar4 = *(int *)(pbVar7 + 4);
          goto LAB_00284e54;
        }
        pbVar7 = pbVar7 + 8;
      } while (pbVar7 != pbVar17 + 0x70);
      bVar1 = *pbVar17;
      iVar4 = *(int *)(pbVar17 + 4);
      iVar13 = net_ad_wrap_service(param_1);
      *(byte *)(param_2 * 0xd18 + iVar13 + 0x1138) = bVar1;
      uVar8 = (uint)bVar1;
LAB_00284e54:
      uVar11 = local_30 * iVar4;
      if (local_34 == 1) {
        uVar11 = (uVar11 * 100) / 0x5a;
      }
      else if (local_34 == 2) {
        uVar11 = (uVar11 * 100) / 0x55;
      }
      else if ((local_34 != 0) && (-1 < DebugLevel)) {
        printk("%s: invalid gi=%d, ignored as 0.\n","mt_ate_get_txlen_by_pkt_tx_time",local_34);
      }
      uVar14 = 1;
      uVar15 = (iVar12 * uVar11) / 0x50;
      iVar4 = DebugLevel;
      uVar9 = uVar8;
    }
    else if (uVar10 == 10) {
      iVar5 = net_ad_wrap_service(param_1);
      puVar18 = &UNK_002a6ef8;
      iVar5 = iVar5 + iVar13;
      uVar8 = *(byte *)(iVar5 + 0xa2c) & 0xf;
      uVar11 = *(uint *)(iVar5 + 0xa28) >> 1 & 0xff;
      if (uVar11 < 0x25) {
        iVar4 = 0;
LAB_00284ff8:
        if ((*(byte *)(iVar5 + 0xa2c) & 0x20) == 0) {
          uVar3 = (&DAT_002a6efa)[iVar4 * 5];
        }
        else {
          uVar3 = (&DAT_002a6efc)[iVar4 * 5];
        }
        if (uVar3 != 0) {
          local_30 = (uint)*(byte *)(iVar5 + 0xa34);
          bVar1 = (&DAT_002a6eec)[uVar8];
          iVar4 = (uint)(byte)(&DAT_002a6f5c)[uVar8] * uVar3 * local_30;
          *(int *)(iVar5 + 0xa5c) = iVar4;
          iVar4 = __aeabi_uidiv((bVar1 - 1) * iVar4);
          *(int *)(iVar5 + 0xa58) = iVar4;
          iVar13 = FUN_0027f65c(10,local_34);
          iVar6 = FUN_0027f5ec(10,local_34);
          uVar2 = (&DAT_002a6b30)[iVar6];
          iVar13 = (iVar12 * 5 + -200) -
                   (uint)(byte)(&DAT_002a6b20)[local_30] * (uint)(byte)(&DAT_002a6b2c)[iVar13];
          __aeabi_uidivmod(iVar13,uVar2);
          if (extraout_r1 == 0) {
            uVar11 = __aeabi_uidiv(iVar13,uVar2);
          }
          else {
            iVar13 = __aeabi_uidiv(iVar13,uVar2);
            uVar11 = iVar13 + 1;
          }
          if (0x3ffe < uVar11) {
            uVar11 = 0x3fff;
          }
          uVar15 = iVar4 * uVar11 - 0x16 >> 3;
          if (0 < DebugLevel) {
            printk("\t%s: \tsymbol=%d, PSDU length:%d (0x3fff is H/W limiation)\n",
                   "mt_ate_calc_bytes_by_time",uVar11,uVar15);
          }
          iVar4 = DebugLevel;
          uVar15 = uVar15 - 0xd;
          *(uint *)(iVar5 + 0xa3c) = uVar15;
          uVar14 = 1;
          uVar11 = 0;
          goto LAB_00284994;
        }
      }
      else {
        iVar4 = 1;
        do {
          pbVar17 = puVar18 + 10;
          puVar18 = puVar18 + 10;
          if (uVar11 < *pbVar17) goto LAB_00284ff8;
          iVar4 = iVar4 + 1;
        } while (iVar4 != 7);
      }
      if (DebugLevel < 0) {
        uVar15 = 0x3f3;
        goto LAB_002849a4;
      }
      uVar14 = 1;
      printk("%s: unknown RU Index:[%d], forced transmit l024 bytes MPDU!\n",
             "mt_ate_get_txlen_by_pkt_tx_time");
      uVar11 = 0;
      uVar15 = 0x3f3;
      local_30 = 1;
      iVar4 = DebugLevel;
    }
    else {
      uVar11 = 0;
      uVar14 = 1;
      uVar15 = 0;
      local_30 = 1;
      iVar4 = DebugLevel;
    }
  }
LAB_00284994:
  if ((0 < iVar4) &&
     (printk("%s: phy_mode=%d, mcs/mcs_1ss=%d/%d, nss=%d, bw/bw_fact=%d/%d, sgi=%d\n",
             "mt_ate_get_txlen_by_pkt_tx_time",uVar10,uVar8,uVar9,local_30,uVar16,uVar14,local_34),
     0 < DebugLevel)) {
    printk("%s: txlen=%d, pkt_tx_time=%d, tx_data_rate=%d\n","mt_ate_get_txlen_by_pkt_tx_time",
           uVar15,iVar12,uVar11,local_30,uVar16,uVar14,local_34);
  }
  if (uVar10 < 5) {
    if (uVar10 != 4) {
      if (uVar10 - 2 < 2) {
        if (uVar15 < 65000) {
          return uVar15;
        }
        if (0 < DebugLevel) {
          printk("%s: Expected txlen > HT mode PPDU max length, reduce the txlen=%d\n",
                 "mt_ate_get_txlen_by_pkt_tx_time",65000);
          return 65000;
        }
        return 65000;
      }
      if (uVar10 == 1) {
        if (uVar15 < 0x900) {
          return uVar15;
        }
        if (0 < DebugLevel) {
          printk("%s: Expected txlen > OFDM mode PPDU max length, reduce the txlen=%d\n",
                 "mt_ate_get_txlen_by_pkt_tx_time",0x900);
          return 0x900;
        }
      }
      else {
        if (uVar15 < 0x900) {
          return uVar15;
        }
        if (0 < DebugLevel) {
          printk("%s: Expected txlen > CCK mode PPDU max length, reduce the txlen=%d\n",
                 "mt_ate_get_txlen_by_pkt_tx_time",0x900);
          return 0x900;
        }
      }
      return 0x900;
    }
    if (uVar15 < 0x68b00) {
      return uVar15;
    }
    if (0 < DebugLevel) {
      printk("%s: Expected txlen > VHT mode PPDU max length, reduce the txlen=%d\n",
             "mt_ate_get_txlen_by_pkt_tx_time",0x68b00);
      return 0x68b00;
    }
    return 0x68b00;
  }
LAB_002849a4:
  if (0x1a2bff < uVar15) {
    if (DebugLevel < 1) {
      uVar15 = 0x1a2c00;
    }
    else {
      printk("%s: Expected txlen > HE mode PPDU max length, reduce the txlen=%d\n",
             "mt_ate_get_txlen_by_pkt_tx_time",0x1a2c00);
      uVar15 = 0x1a2c00;
    }
  }
  return uVar15;
}

