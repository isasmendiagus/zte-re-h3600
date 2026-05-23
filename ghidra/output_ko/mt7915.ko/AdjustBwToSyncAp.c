// module: mt7915.ko
// function: AdjustBwToSyncAp @ 0x1035c4
// size: 2148 bytes
//

ushort AdjustBwToSyncAp(int param_1,int param_2,int param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  byte bVar12;
  ushort uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint local_5c;
  int local_58;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar5 = GetStaCfgByWdev(param_1,param_3);
  uVar6 = wlan_operate_get_ht_bw(param_3);
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (param_2 == 0 || iVar5 == 0) {
    return 0;
  }
  uVar14 = (uint)*(ushort *)(iVar5 + 0x2132e0);
  iVar7 = wlan_config_get_ht_bw(param_3);
  uVar4 = *(ushort *)(param_3 + 0x18);
  uVar13 = uVar4 & 0x18;
  if ((((uVar4 & 0x18) != 0) && (uVar13 = 0, (*(uint *)(param_2 + 0xa8) & 2) != 0)) &&
     (uVar13 = (ushort)(param_2 == 0 || iVar5 == 0), *(byte *)(param_3 + 0x1a) < 0xe)) {
    iVar11 = wlan_operate_get_ht_bw(param_3);
    uVar8 = wlan_operate_get_ext_cha(param_3);
    if (iVar11 == 1) {
      if (((*(byte *)(param_2 + 0xf7) & 7) == 0) || (*(char *)(param_2 + 0xa3) == '\0')) {
        FUN_00102018(param_1,*(undefined2 *)(iVar5 + 0x2132e0),0,0);
        if (2 < DebugLevel) {
          printk("FallBack APClient BW to 20MHz\n");
        }
LAB_001039e4:
        if ((&DAT_0036790d)[param_1] != '\0') {
          iVar7 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
          uVar9 = wlan_operate_get_ht_bw(param_3);
          uVar10 = wlan_operate_get_ext_cha(param_3);
          uVar8 = (uint)*(byte *)(iVar7 + 0x14a);
          if (uVar8 != 0) {
            uVar15 = 0;
            do {
              iVar11 = uVar15 * 0x42f4 + *(int *)(&DAT_003687a8 + param_1);
              if ((((iVar11 != 0) && (*(char *)(iVar11 + 5) == '\x02')) &&
                  (*(int *)(iVar11 + 0x4140) == iVar5)) && (*(int *)(iVar11 + 0x4144) != 0)) {
                FUN_00102018(param_1,*(undefined2 *)(*(int *)(iVar11 + 0x4144) + 0xe0),uVar9,uVar10)
                ;
                uVar8 = (uint)*(byte *)(iVar7 + 0x14a);
              }
              uVar15 = uVar15 + 1 & 0xff;
            } while (uVar15 < uVar8);
          }
          if (2 < DebugLevel) {
            printk("FallBack APClient BW to (%d)\n",uVar9);
            uVar4 = *(ushort *)(param_3 + 0x18);
            uVar13 = 1;
            goto LAB_00103678;
          }
        }
        uVar4 = *(ushort *)(param_3 + 0x18);
        uVar13 = 1;
        goto LAB_00103678;
      }
    }
    else if (iVar7 != 0 && iVar11 == 0) {
      bVar12 = *(byte *)(param_2 + 0xf7);
      if (((((bVar12 & 3) != 0) && ((bVar12 & 4) != 0)) &&
          (((*(uint *)(param_2 + 0xa8) & 1) != 0 && ((*(byte *)(param_2 + 0xdc) & 2) != 0)))) &&
         ((uVar8 == 0 || ((bVar12 & 3) == uVar8)))) {
        FUN_00102018(param_1,*(undefined2 *)(iVar5 + 0x2132e0),1,bVar12 & 3);
        wlan_operate_set_prim_ch(param_3,*(undefined1 *)(param_3 + 0x1a));
        if (2 < DebugLevel) {
          printk("FallBack Client/APClient BW to 40MHz\n");
        }
        goto LAB_001039e4;
      }
    }
    uVar4 = *(ushort *)(param_3 + 0x18);
    uVar13 = 0;
  }
LAB_00103678:
  if ((uVar4 & 0x20) == 0) {
    return uVar13;
  }
  if (*(char *)(iVar5 + 0x40f2) != '\x01') {
    return uVar13;
  }
  if ((*(uint *)(param_2 + 0xa8) & 10) != 10) {
    return uVar13;
  }
  uVar15 = (uint)*(byte *)(param_2 + 0x119);
  uVar16 = (uint)*(byte *)(param_2 + 0x11a);
  uVar8 = wlan_operate_get_vht_bw(param_3);
  local_5c = (uint)*(byte *)(param_2 + 0x118);
  if ((*(byte *)(param_2 + 0xf7) & 7) == 0) {
LAB_00103790:
    iVar7 = wlan_operate_get_ht_bw(param_3);
    if (iVar7 == 0) {
      return uVar13;
    }
    iVar7 = wlan_operate_get_vht_bw(param_3);
    if (iVar7 == 0) {
      iVar7 = 1;
      local_58 = 0;
    }
    else {
      iVar7 = wlan_operate_get_vht_bw(param_3);
      if (iVar7 == 1) {
        iVar7 = 2;
        local_58 = 0;
      }
      else {
        local_58 = 0;
        iVar7 = wlan_operate_get_vht_bw(param_3);
        if (iVar7 != 2) {
LAB_00103c54:
          iVar7 = wlan_operate_get_vht_bw(param_3);
          if (iVar7 == 3) {
            iVar7 = 3;
          }
          else {
            iVar7 = 0;
          }
          goto LAB_00103b4c;
        }
        iVar7 = 3;
      }
    }
  }
  else {
    if (local_5c == 0) {
      local_58 = 1;
    }
    else if (local_5c == 1) {
      if (uVar8 != 1) {
        if (uVar8 < 2) goto LAB_00103790;
        if (uVar16 != 0) {
          if (uVar15 < uVar16) {
            uVar15 = uVar16 - uVar15;
          }
          else {
            uVar15 = uVar15 - uVar16;
          }
          if ((uVar15 & 0xff) == 8) {
            local_5c = 2;
            local_58 = 3;
          }
          else {
            if ((uVar15 & 0xff) < 0x10) goto LAB_00103790;
            uVar8 = wlan_operate_get_cen_ch_2(param_3);
            if (uVar8 == uVar16) {
              local_5c = 3;
              local_58 = 3;
            }
            else {
              local_5c = 3;
              wlan_operate_set_cen_ch_2(param_3);
              local_58 = 3;
            }
          }
          goto LAB_00103b14;
        }
      }
      local_58 = 2;
    }
    else {
      if (1 < local_5c - 2) goto LAB_00103790;
      local_58 = 3;
    }
LAB_00103b14:
    iVar7 = wlan_operate_get_ht_bw(param_3);
    if (iVar7 == 0) {
      iVar7 = 0;
    }
    else {
      iVar7 = wlan_operate_get_vht_bw(param_3);
      if (iVar7 == 0) {
        iVar7 = 1;
      }
      else {
        iVar7 = wlan_operate_get_vht_bw(param_3);
        if (iVar7 == 1) {
          iVar7 = 2;
        }
        else {
          iVar7 = wlan_operate_get_vht_bw(param_3);
          if (iVar7 != 2) goto LAB_00103c54;
          iVar7 = 3;
        }
      }
LAB_00103b4c:
      if (iVar7 == local_58) {
        return uVar13;
      }
    }
  }
  uVar8 = get_channel_bw_cap(iVar5,*(undefined1 *)(iVar5 + 0x1a));
  if (2 < DebugLevel) {
    printk("SYNC - Peer AP Changed VHT BW[old:new] = [%u:%u], HT BW[old:new] = [%u:%u]\n",iVar7,
           local_58,uVar6,((uint)*(byte *)(param_2 + 0xf7) << 0x1d) >> 0x1f);
  }
  *(uint *)(iVar5 + 0x2123ec) = *(uint *)(iVar5 + 0x2123ec) | 8;
  memmove((void *)(iVar5 + 0x41d8),(void *)(param_2 + 0x118),5);
  if (((*(char *)(param_2 + 0x118) == '\x01' && 1 < uVar8) ||
      (((uint)*(byte *)(param_2 + 0xf7) << 0x1d) >> 0x1f != (uVar6 & 0xffff))) ||
     (*(char *)(param_2 + 0x118) != '\x01')) {
    wlan_operate_set_vht_bw(iVar5,local_5c);
  }
  iVar7 = uVar14 * 0x14c0 + param_1 + 0xa1d20;
  if ((iVar7 != 0) && ((*(uint *)(param_2 + 0xa8) & 4) != 0)) {
    *(uint *)(iVar5 + 0x2123ec) = *(uint *)(iVar5 + 0x2123ec) | 4;
    memmove((void *)(iVar5 + 0x41cc),(void *)(param_2 + 0x10c),0xc);
    uVar6 = wlan_operate_get_tx_stream(param_3);
    if (uVar6 != 0) {
      bVar1 = false;
      bVar2 = false;
      bVar3 = false;
      do {
        while( true ) {
          while( true ) {
            while( true ) {
              uVar6 = uVar6 - 1 & 0xff;
              uVar8 = uVar6 + 1 & 0xff;
              if (uVar8 != 3) break;
              if (((uint)*(byte *)(param_2 + 0x110) << 0x1a) >> 0x1e != 3) {
                bVar2 = true;
              }
            }
            if (uVar8 != 4) break;
            if (*(byte *)(param_2 + 0x110) >> 6 != 3) {
              bVar1 = true;
            }
          }
          if (uVar8 != 2) break;
          if (((uint)*(byte *)(param_2 + 0x110) << 0x1c) >> 0x1e != 3) {
            bVar3 = true;
          }
        }
      } while (uVar6 != 0);
      goto LAB_00103878;
    }
  }
  bVar1 = false;
  bVar2 = false;
  bVar3 = false;
LAB_00103878:
  *(byte *)(iVar5 + 0x41ab) =
       *(byte *)(iVar5 + 0x41ab) & 0xfb |
       (byte)((((uint)*(byte *)(param_2 + 0xf7) << 0x1d) >> 0x1f) << 2);
  *(byte *)(iVar5 + 0x41ab) = *(byte *)(iVar5 + 0x41ab) & 0xfc | *(byte *)(param_2 + 0xf7) & 3;
  wlan_operate_set_ht_bw(param_3);
  iVar11 = uVar14 * 0x14c0 + param_1;
  *(ushort *)(iVar11 + 0xa1ddc) =
       *(ushort *)(iVar11 + 0xa1ddc) & 0xfe7f |
       (ushort)((((uint)*(byte *)(iVar5 + 0x41ab) << 0x1d) >> 0x1f) << 7);
  bVar12 = *(byte *)(iVar11 + 0xa2a41);
  *(undefined1 *)(iVar11 + 0xa2a40) = 1;
  *(byte *)(iVar11 + 0xa2a41) = bVar12 & 0x7f;
  if (bVar1) {
    *(byte *)(iVar11 + 0xa2a41) = bVar12 & 0xf | 0x30;
  }
  else {
    bVar12 = *(byte *)(iVar11 + 0xa2a41);
    if (bVar2) {
      *(byte *)(iVar11 + 0xa2a41) = bVar12 & 0x8f | 0x20;
    }
    else {
      if (bVar3) {
        bVar12 = bVar12 & 0x8f | 0x10;
      }
      else {
        bVar12 = bVar12 & 0x8f;
      }
      *(byte *)(iVar11 + 0xa2a41) = bVar12;
    }
  }
  iVar11 = param_1 + uVar14 * 0x14c0;
  *(byte *)(iVar11 + 0xa2a41) = *(byte *)(iVar11 + 0xa2a41) & 0xf3;
  *(undefined1 *)(iVar5 + 0x41de) = *(undefined1 *)(iVar11 + 0xa2a40);
  *(undefined1 *)(iVar5 + 0x41df) = *(undefined1 *)(param_1 + uVar14 * 0x14c0 + 0xa2a41);
  __memzero(&local_44,0x1c);
  local_40 = 1;
  RAParamUpdate(param_1,iVar7,&local_44);
  return 1;
}

