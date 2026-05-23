// module: mt7915.ko
// function: net_ad_thread @ 0x25dc54
// size: 1348 bytes
//

int net_ad_thread(int param_1)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  byte bVar7;
  char cVar8;
  uint *puVar9;
  int iVar10;
  uint uVar11;
  uint *puVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  uint uVar22;
  bool bVar23;
  int local_54;
  int local_48;
  undefined1 auStack_2c [8];
  
  if (param_1 != 0) {
    iVar18 = *(int *)(param_1 + 0x10);
    puVar9 = *(uint **)(param_1 + 0x14);
    iVar4 = RtmpOsGetNetDevPriv(*(undefined4 *)(iVar18 + 4));
    if (iVar4 != 0) {
      complete(&DAT_005f6408);
      bVar1 = *(byte *)(param_1 + 0x18);
      if (bVar1 == 0) {
        do {
          iVar5 = sys_ad_wait_os_task(0,param_1,auStack_2c);
          if (iVar5 == 0) {
            uVar15 = *(uint *)(iVar4 + 0xa39f84);
            goto LAB_0025dfb8;
          }
          _raw_spin_lock_bh(&DAT_005f63fc);
          bVar7 = DAT_005f6400;
          while (bVar7 != 0) {
            if ((bVar7 & 1) == 0) {
              if ((*(char *)(iVar18 + 0x34) == '\0') || ((bVar7 & 2) == 0)) {
                DAT_005f6400 = bVar7;
                _raw_spin_unlock_bh(&DAT_005f63fc);
                _LANCHOR2 = 0;
                *(uint *)(iVar4 + 0xa39f84) = *(uint *)(iVar4 + 0xa39f84) & 0xffffffbf;
                return 0;
              }
              bVar7 = bVar7 & 0xfd;
              local_54 = 1;
            }
            else {
              bVar7 = bVar7 & 0xfe;
              local_54 = 0;
            }
            iVar5 = RtmpOsGetNetDevPriv(*(undefined4 *)(iVar18 + 4));
            if (iVar5 != 0) {
              if (*(int *)(iVar5 + 0x285ae8) == 0) {
                uVar15 = 0x200;
              }
              else {
                uVar15 = (uint)*(ushort *)(*(int *)(iVar5 + 0x285ae8) + 2);
              }
              bVar23 = *(char *)(iVar18 + 0x70) != '\0';
              if (bVar23) {
                iVar14 = 0x285b4c;
                iVar10 = iVar5 + local_54 * 0x10;
              }
              else {
                iVar14 = iVar5 + 0x285b4c;
                iVar10 = 0;
              }
              if (bVar23) {
                iVar14 = iVar10 + iVar14;
              }
              iVar21 = local_54 * 0xd18;
              uVar17 = puVar9[local_54 * 0x346];
              uVar22 = puVar9[local_54 * 0x346 + 0x30e];
              uVar13 = puVar9[local_54 * 0x346 + 0x310];
              cVar2 = *(char *)((int)puVar9 +
                               (uint)*(byte *)((int)puVar9 + iVar21 + 0x216) * 0x20 + iVar21 + 0x35a
                               );
              uVar19 = puVar9[local_54 * 0x346 + 0x304];
              uVar20 = puVar9[local_54 * 0x346 + 0x305];
              uVar3 = hif_get_resource_idx
                                (*(undefined4 *)(iVar5 + 0xa797a0),puVar9[0x9f],2,
                                 *(undefined1 *)((int)puVar9 + iVar21 + 0x2e));
              local_48 = DAT_005f6404;
              iVar10 = hif_get_tx_resource_free_num(*(undefined4 *)(iVar5 + 0xa797a0),uVar3);
              if ((uVar17 & 0x100) == 0) {
                uVar16 = uVar19;
                while( true ) {
                  uVar11 = ((uVar17 ^ 2) << 0x1e) >> 0x1f;
                  if (iVar10 == 0) {
                    uVar11 = 1;
                  }
                  if (uVar11 != 0) break;
                  while( true ) {
                    if (((uVar20 != 0 || uVar19 != 0) && (uVar15 <= *(uint *)(iVar14 + 8))) ||
                       (uVar22 <= uVar13)) goto LAB_0025def8;
                    uVar11 = (uint)*(byte *)((int)puVar9 + iVar21 + 0x216);
                    bVar23 = cVar2 != '\0';
                    if (bVar23 && uVar19 != 0) {
                      uVar16 = 1;
                    }
                    if (!bVar23 || uVar19 == 0) {
                      uVar16 = 0;
                    }
                    iVar10 = net_ad_enq_pkt(iVar18,uVar16,puVar9[local_54 * 0x346 + uVar11 + 0x9f],
                                            puVar9[local_54 * 0x346 + uVar11 + 0xaf],
                                            puVar9[local_54 * 0x346 + uVar11 + 0xbf]);
                    if (iVar10 != 0) goto LAB_0025def8;
                    uVar13 = uVar13 + 1;
                    cVar8 = *(char *)((int)puVar9 + iVar21 + 0x216) + '\x01';
                    *(char *)((int)puVar9 + iVar21 + 0x216) = cVar8;
                    if (*(char *)((int)puVar9 + iVar21 + 0x215) == cVar8) {
                      *(undefined1 *)((int)puVar9 + iVar21 + 0x216) = 0;
                    }
                    uVar11 = uVar16;
                    if (uVar20 != 0) {
                      uVar11 = uVar16 | 1;
                    }
                    if (uVar11 == 0) break;
                    uVar6 = hc_get_ct_cb(*(undefined4 *)(iVar18 + 0x30));
                    iVar10 = 0;
                    if (*(char *)(iVar18 + 0x70) != '\0') {
                      iVar10 = local_54;
                    }
                    iVar10 = token_tx_get_queue_by_band(uVar6,iVar10);
                    uVar11 = token_tx_get_free_cnt();
                    uVar16 = *(uint *)(iVar10 + 0x10);
                    iVar10 = hif_get_tx_resource_free_num(*(undefined4 *)(iVar5 + 0xa797a0),uVar3);
                    if ((iVar10 == 0 || uVar11 <= uVar16 - 100) || (uVar15 <= *(uint *)(iVar14 + 8))
                       ) break;
                  }
                  local_48 = local_48 + -1;
                  if (local_48 == 0) break;
                  iVar10 = hif_get_tx_resource_free_num(*(undefined4 *)(iVar5 + 0xa797a0),uVar3);
                }
              }
LAB_0025def8:
              puVar9[local_54 * 0x346 + 0x310] = uVar13;
              puVar9[local_54 * 0x346 + 0x30e] = uVar22;
            }
          }
          DAT_005f6400 = bVar1;
          _raw_spin_unlock_bh(&DAT_005f63fc);
          if ((*puVar9 & 0x40) != 0) {
            puVar12 = puVar9 + 0x335;
            if ((puVar9[0x33a] == 0) || (puVar9[0x336] == 0)) {
              printk("%s: mps_cb/mps_setting NULL %p/%p\n","net_ad_mps_check_stat",puVar12);
              iVar5 = 0x607;
              uVar15 = *(uint *)(iVar4 + 0xa39f84);
              goto LAB_0025e0f8;
            }
            if (puVar9[0x310] < puVar9[0x30e]) {
              uVar15 = 0;
            }
            else {
              uVar15 = puVar9[0x337] & 1;
            }
            if (uVar15 == 0) {
LAB_0025df80:
              iVar5 = FUN_0025c704(iVar18,puVar9);
              if (iVar5 == 0) goto LAB_0025df94;
            }
            else {
              _raw_spin_lock_bh(puVar12);
              puVar9[0x337] = 0;
              _raw_spin_unlock_bh(puVar12);
              if (puVar9[0x339] <= puVar9[0x336]) goto LAB_0025df80;
              *(undefined1 *)(puVar9 + 0x338) = 0;
              *puVar9 = *puVar9 & 0xffffffbf;
              iVar5 = net_ad_mps_tx_operation(iVar18,puVar9,0);
              if (iVar5 == 0) goto LAB_0025df80;
            }
            uVar15 = *(uint *)(iVar4 + 0xa39f84);
LAB_0025e0f8:
            *(uint *)(iVar4 + 0xa39f84) = uVar15 & 0xffffffbf;
            _LANCHOR2 = 0;
            printk(&_LC60,"net_ad_thread",iVar5);
            return iVar5;
          }
LAB_0025df94:
          schedule();
        } while (*(char *)(param_1 + 0x18) == '\0');
        uVar15 = *(uint *)(iVar4 + 0xa39f84);
      }
      else {
        uVar15 = *(uint *)(iVar4 + 0xa39f84);
      }
LAB_0025dfb8:
      *(uint *)(iVar4 + 0xa39f84) = uVar15 & 0xffffffbf;
      _LANCHOR2 = 0;
      return 0;
    }
  }
  _LANCHOR2 = 0;
  return 0;
}

