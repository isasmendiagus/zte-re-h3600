// module: mt7915.ko
// function: ba_resource_dump_all @ 0xa4c20
// size: 1964 bytes
//

void ba_resource_dump_all(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  ushort *puVar7;
  int *piVar8;
  int *piVar9;
  uint uVar10;
  uint *puVar11;
  int iVar12;
  ushort *puVar13;
  int iVar14;
  undefined2 *puVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined *local_32;
  undefined2 local_2e [2];
  char local_2a;
  
  puVar13 = (ushort *)((int)&DAT_000a2a00 + param_1 + 2);
  iVar1 = HcGetMaxStaNum(param_1);
  iVar12 = 0;
  puVar11 = (uint *)(param_1 + 0xa1d20);
  if (0 < iVar1) {
    do {
      uVar3 = *puVar11;
      if (uVar3 != 0) {
        if ((uVar3 - 0x20001 & 0xfffdffff) == 0 || uVar3 == 2) {
          if (puVar11[0x3f] == 2) {
            if (uVar3 != 2) goto LAB_000a4c94;
            local_2e[0] = 0x69;
            goto LAB_000a4ca8;
          }
        }
        else {
LAB_000a4c94:
          if (uVar3 == 0x40001) {
            local_32 = (undefined *)0x65706552;
            local_2e[0]._0_1_ = 'a';
            local_2e[0]._1_1_ = 't';
            local_2e[1]._0_1_ = 'e';
            local_2e[1]._1_1_ = 'r';
            local_2a = '\0';
          }
          else {
LAB_000a4ca8:
            if ((uVar3 & 4) == 0) {
              if ((uVar3 & 8) == 0) {
                local_32 = &DAT_00415453;
              }
              else {
                local_32 = (undefined *)0x6873654d;
                    /* WARNING: Ignoring partial resolution of indirect */
                local_2e[0]._0_1_ = 0;
              }
            }
            else {
              local_32 = &DAT_00534457;
            }
          }
          if ((0 < DebugLevel) &&
             (printk("%02x:%02x:%02x:%02x:%02x:%02x (Aid = %d) (%s) -\n",(char)puVar11[0x3b],
                     *(undefined1 *)((int)puVar11 + 0xed),*(undefined1 *)((int)puVar11 + 0xee),
                     *(undefined1 *)((int)puVar11 + 0xef),(char)puVar11[0x3c],
                     *(undefined1 *)((int)puVar11 + 0xf1),(short)puVar11[0x3e],&local_32),
             0 < DebugLevel)) {
            printk("[Originator]\n");
          }
          iVar5 = 0;
          iVar1 = DebugLevel;
          puVar7 = puVar13;
          do {
            puVar7 = puVar7 + 1;
            if (((*puVar7 != 0) &&
                (iVar4 = (uint)*puVar7 * 0x48, *(int *)(param_1 + iVar4 + 0x1b1cc) == 3)) &&
               (0 < iVar1)) {
              iVar4 = param_1 + 0x1c0 + iVar4;
              printk("TID=%d, BAWinSize=%d, StartSeq=%d, CurTxSeq=%d\n",iVar5,
                     *(undefined2 *)(iVar4 + 0x1b004),*(undefined2 *)(iVar4 + 0x1b008),
                     *(undefined2 *)
                      (param_1 + 0x1c0 + (iVar5 + (uint)(ushort)puVar11[0x38] * 0x310 + 0x17a78) * 2
                      + 4));
              iVar1 = DebugLevel;
            }
            iVar5 = iVar5 + 1;
          } while (iVar5 != 8);
          if ((0 < iVar1) && (printk(&_LC17), iVar1 = DebugLevel, 0 < DebugLevel)) {
            printk("[Recipient]\n");
            iVar1 = DebugLevel;
          }
          iVar5 = 0;
          puVar6 = (ushort *)((int)puVar11 + 0xcd2);
          puVar7 = puVar6;
          do {
            puVar7 = puVar7 + 1;
            if (*puVar7 != 0) {
              iVar4 = (uint)*puVar7 * 0x60;
              iVar14 = param_1 + iVar4;
              if ((*(int *)(iVar14 + 0x1c8) - 3U < 3) && (0 < iVar1)) {
                iVar4 = param_1 + 0x1c0 + iVar4;
                uVar16 = *(undefined4 *)(iVar14 + 500);
                uVar17 = *(undefined4 *)(param_1 + (uint)*(byte *)(iVar14 + 0x1ff) * 0x14 + 0x2f5d4)
                ;
                printk("State=%d, TID=%d, BAWinSize=%d, LastIndSeq=%d, ReorderingPkts=%d, FreeMpduBls=%d\n"
                       ,*(int *)(iVar14 + 0x1c8),iVar5,*(undefined2 *)(iVar4 + 0x14),
                       *(undefined2 *)(iVar4 + 0xc),uVar16,uVar17);
                iVar1 = DebugLevel;
                if (0 < DebugLevel) {
                  printk("drop(duplicated) pkts = %ld, drop(old) pkts = %ld,\t\t\t\t\t\t\t   drop(unknown) state pkts = %ld, sn_large_win_end = %ld\n\n"
                         ,*(undefined4 *)(iVar14 + 0x1dc),*(undefined4 *)(iVar14 + 0x1e0),
                         *(undefined4 *)(iVar14 + 0x1e4),*(undefined4 *)(iVar14 + 0x1e8),uVar16,
                         uVar17);
                  iVar1 = DebugLevel;
                }
              }
            }
            iVar5 = iVar5 + 1;
          } while (iVar5 != 8);
          if ((((param_2 == 1) && (uVar3 = (uint)puVar13[-7], uVar3 != 0)) &&
              (iVar5 = param_1 + uVar3 * 0x60, *(int *)(iVar5 + 0x1c8) - 3U < 2)) &&
             (iVar4 = *(int *)(iVar5 + 0x208), iVar4 != 0)) {
            uVar2 = *(uint *)(iVar5 + 0x20c);
            if (uVar2 < 0x100) {
              iVar14 = uVar2 * 0x14;
              uVar10 = uVar2;
              while( true ) {
                puVar15 = (undefined2 *)(iVar4 + iVar14);
                if ((*(uint *)(param_1 + 0x2f68c) & 4) == 0) {
                  if (0 < iVar1) {
                    printk("idx(%d), wcid(%d) sn(%d), amsdu(%d), type(%d), last_in_seq%d\n",uVar10,
                           puVar15[3],*puVar15,*(undefined1 *)(puVar15 + 1),
                           *(undefined1 *)((int)puVar15 + 3),puVar15[2]);
                    iVar1 = DebugLevel;
                  }
                }
                else if (0 < iVar1) {
                  printk("idx(%d), wcid(%d),\t\t\t\t\t\t\t  ta(%02x:%02x:%02x:%02x:%02x:%02x),\t\t\t\t\t\t\t  ra(%02x:%02x:%02x:%02x:%02x:%02x),\t\t\t\t\t\t\t  sn(%d), amsdu(%d), type(%d), last_in_seq%d\n"
                         ,uVar10,puVar15[3],*(undefined1 *)(puVar15 + 4),
                         *(undefined1 *)((int)puVar15 + 9),*(undefined1 *)(puVar15 + 5),
                         *(undefined1 *)((int)puVar15 + 0xb),*(undefined1 *)(puVar15 + 6),
                         *(undefined1 *)((int)puVar15 + 0xd),*(undefined1 *)(puVar15 + 7),
                         *(undefined1 *)((int)puVar15 + 0xf),*(undefined1 *)(puVar15 + 8),
                         *(undefined1 *)((int)puVar15 + 0x11),*(undefined1 *)(puVar15 + 9),
                         *(undefined1 *)((int)puVar15 + 0x13),*puVar15,*(undefined1 *)(puVar15 + 1),
                         *(undefined1 *)((int)puVar15 + 3),puVar15[2]);
                  iVar1 = DebugLevel;
                }
                uVar10 = uVar10 + 1;
                iVar14 = iVar14 + 0x14;
                if (uVar10 == 0x100) break;
                iVar4 = *(int *)(iVar5 + 0x208);
              }
              if (uVar2 == 0) goto LAB_000a4e14;
            }
            iVar5 = 0;
            uVar10 = 0;
            do {
              puVar15 = (undefined2 *)(*(int *)(param_1 + uVar3 * 0x60 + 0x208) + iVar5);
              if ((*(uint *)(param_1 + 0x2f68c) & 4) == 0) {
                if (0 < iVar1) {
                  printk("idx(%d), wcid(%d) sn(%d), amsdu(%d), type(%d), last_in_seq%d\n",uVar10,
                         puVar15[3],*puVar15,*(undefined1 *)(puVar15 + 1),
                         *(undefined1 *)((int)puVar15 + 3),puVar15[2]);
                  iVar1 = DebugLevel;
                }
              }
              else if (0 < iVar1) {
                printk("idx(%d), wcid(%d),\t\t\t\t\t\t\t  ta(%02x:%02x:%02x:%02x:%02x:%02x),\t\t\t\t\t\t\t  ra(%02x:%02x:%02x:%02x:%02x:%02x),\t\t\t\t\t\t\t  sn(%d), amsdu(%d), type(%d), last_in_seq%d\n"
                       ,uVar10,puVar15[3],*(undefined1 *)(puVar15 + 4),
                       *(undefined1 *)((int)puVar15 + 9),*(undefined1 *)(puVar15 + 5),
                       *(undefined1 *)((int)puVar15 + 0xb),*(undefined1 *)(puVar15 + 6),
                       *(undefined1 *)((int)puVar15 + 0xd),*(undefined1 *)(puVar15 + 7),
                       *(undefined1 *)((int)puVar15 + 0xf),*(undefined1 *)(puVar15 + 8),
                       *(undefined1 *)((int)puVar15 + 0x11),*(undefined1 *)(puVar15 + 9),
                       *(undefined1 *)((int)puVar15 + 0x13),*puVar15,*(undefined1 *)(puVar15 + 1),
                       *(undefined1 *)((int)puVar15 + 3),puVar15[2]);
                iVar1 = DebugLevel;
              }
              uVar10 = uVar10 + 1;
              iVar5 = iVar5 + 0x14;
            } while (uVar10 != uVar2);
          }
LAB_000a4e14:
          if ((0 < iVar1) && (printk(&_LC17), 0 < DebugLevel)) {
            printk("[RX ReorderBuffer]\n");
          }
          do {
            puVar6 = puVar6 + 1;
            uVar3 = (uint)*puVar6;
            if (uVar3 != 0) {
              if (param_1 + uVar3 * 0x60 == -0x1ec) {
                printk(&_LC1,0x5c);
                dump_stack();
              }
              piVar9 = *(int **)(param_1 + uVar3 * 0x60 + 0x1ec);
              if (piVar9 != (int *)0x0) {
                if (0 < DebugLevel) {
                  printk("mpdu:SN = %d, AMSDU = %d\n",piVar9[5],(char)piVar9[6]);
                  piVar8 = (int *)piVar9[1];
                  goto joined_r0x000a51d4;
                }
                piVar8 = (int *)piVar9[1];
                if (piVar8 != (int *)0x0) {
                  while( true ) {
                    piVar8 = (int *)*piVar8;
joined_r0x000a51d4:
                    if (piVar8 == (int *)0x0) break;
                    if (0 < DebugLevel) {
                      printk("msdu:SN = %d, AMSDU = %d\n",piVar8[5],*(undefined1 *)(piVar8 + 6));
                    }
                  }
                }
                while (piVar9 = (int *)*piVar9, piVar9 != (int *)0x0) {
                  printk("mpdu:SN = %d, AMSDU = %d\n",piVar9[5],*(undefined1 *)(piVar9 + 6));
                  for (piVar8 = (int *)piVar9[1]; piVar8 != (int *)0x0; piVar8 = (int *)*piVar8) {
                    if (0 < DebugLevel) {
                      printk("msdu:SN = %d, AMSDU = %d\n",piVar8[5],*(undefined1 *)(piVar8 + 6));
                    }
                  }
                }
              }
            }
          } while (puVar6 != puVar13);
        }
      }
      puVar13 = puVar13 + 0xa60;
      iVar12 = iVar12 + 1;
      puVar11 = puVar11 + 0x530;
      iVar1 = HcGetMaxStaNum(param_1);
    } while (iVar12 < iVar1);
  }
  return;
}

