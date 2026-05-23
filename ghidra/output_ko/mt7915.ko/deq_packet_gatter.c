// module: mt7915.ko
// function: deq_packet_gatter @ 0xd2ae4
// size: 1784 bytes
//

undefined4 deq_packet_gatter(int param_1,int param_2,undefined1 *param_3)

{
  byte bVar1;
  ushort uVar2;
  char cVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  undefined4 uVar13;
  int *piVar14;
  
  uVar12 = (uint)*(ushort *)(param_2 + 8);
  bVar1 = *(byte *)(param_2 + 3);
  uVar11 = (uint)bVar1;
  if (3 < DebugLevel) {
    printk("-->%s(): deq_info->wcid=%d, qidx=%d!\n","deq_packet_gatter",uVar12,uVar11);
  }
  uVar13 = 0;
  *(undefined4 *)(param_2 + 0x20) = 0;
  iVar6 = param_1 + 0x1c0 + (uVar11 + uVar12 * 0x188) * 4 + 0x2f574;
  iVar10 = param_1 + (uVar11 + uVar12 * 0x62) * 0x10;
  _raw_spin_lock_bh(iVar6);
  iVar9 = DebugLevel;
  piVar14 = *(int **)(iVar10 + 0x2f6c4);
  if (piVar14 != (int *)0x0) goto LAB_000d2c90;
  iVar7 = *(int *)(param_3 + 0x48);
  if (iVar7 == 0) {
    *(int *)(param_2 + 0x20) = *(int *)(param_2 + 0x20) + 1;
    if (3 < iVar9) {
      printk("<--%s():Try deQ a empty Q. pTxBlk.TxPktList.Num=%d, deq_info.pkt_cnt=%d\n",
             "deq_packet_gatter",*(undefined4 *)(param_3 + 0x48),*(undefined4 *)(param_2 + 0x18));
    }
  }
  else {
    while (param_3[5] == '\x04') {
      piVar14 = *(int **)(iVar10 + 0x2f6c4);
      if (piVar14 == (int *)0x0) {
LAB_000d2f14:
        if (iVar7 == 1) {
          param_3[5] = 2;
          param_1 = param_1 + uVar12 * 0x620;
          *(int *)(param_1 + 0x2fb58) = *(int *)(param_1 + 0x2fb58) + 1;
        }
        else if (iVar7 == 2) {
          param_1 = param_1 + uVar12 * 0x620;
          *(int *)(param_1 + 0x2fb84) = *(int *)(param_1 + 0x2fb84) + 1;
        }
        else if (iVar7 == 3) {
          param_1 = param_1 + uVar12 * 0x620;
          *(int *)(param_1 + 0x2fbb0) = *(int *)(param_1 + 0x2fbb0) + 1;
        }
        else if (iVar7 == 4) {
          param_1 = param_1 + uVar12 * 0x620;
          *(int *)(param_1 + 0x2fbdc) = *(int *)(param_1 + 0x2fbdc) + 1;
        }
        else if (iVar7 == 5) {
          param_1 = param_1 + uVar12 * 0x620;
          *(int *)(param_1 + 0x2fc08) = *(int *)(param_1 + 0x2fc08) + 1;
        }
        else if (iVar7 == 6) {
          param_1 = param_1 + uVar12 * 0x620;
          *(int *)(param_1 + 0x2fc34) = *(int *)(param_1 + 0x2fc34) + 1;
        }
        else if (iVar7 == 7) {
          param_1 = param_1 + uVar12 * 0x620;
          *(int *)(param_1 + 0x2fc60) = *(int *)(param_1 + 0x2fc60) + 1;
        }
        else if (iVar7 == 8) {
          param_1 = param_1 + uVar12 * 0x620;
          *(int *)(param_1 + 0x2fc8c) = *(int *)(param_1 + 0x2fc8c) + 1;
        }
        break;
      }
LAB_000d2c90:
      iVar9 = *piVar14;
      *piVar14 = 0;
      *(int *)(iVar10 + 0x2f6c4) = iVar9;
      if (iVar9 == 0) {
        *(undefined4 *)(iVar10 + 0x2f6c8) = 0;
      }
      iVar7 = param_1 + uVar12 * 0x620;
      iVar9 = param_1 + (uVar11 + uVar12 * 0x62) * 0x10;
      *(int *)(iVar9 + 0x2f6cc) = *(int *)(iVar9 + 0x2f6cc) + -1;
      *(int *)(iVar7 + 0x2f714) = *(int *)(iVar7 + 0x2f714) + -1;
      if (*(ushort *)((int)piVar14 + 0x42) != uVar12) {
        printk(&_LC42,0x490);
        dump_stack();
      }
      if (param_3[3] == '\0') {
        uVar13 = wdev_search_by_pkt(param_1,piVar14);
        uVar4 = hif_get_resource_idx(*(undefined4 *)(param_1 + 0xa797a0),uVar13,0,uVar11);
        *param_3 = uVar4;
      }
      if (3 < DebugLevel) {
        printk("-->%s(): GetPacket, wcid=%d, deq_pkt_cnt=%d, TotalFrameNum=%d, TotalFrameLen = %d\n"
               ,"deq_packet_gatter",uVar12,*(undefined4 *)(param_2 + 0x20),param_3[3],
               *(undefined2 *)(param_3 + 6));
      }
      cVar3 = tx_pkt_classification(param_1,piVar14,param_3);
      param_3[5] = cVar3;
      if (cVar3 == '\x04') {
        if (param_3[3] == '\0') goto LAB_000d2bf0;
        iVar9 = FUN_000cfd30(param_1,piVar14,param_3);
        if (iVar9 != 0) {
          iVar7 = *(int *)(param_3 + 0x14);
          iVar9 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
          if ((byte)param_3[3] < *(byte *)(iVar9 + 0x1c5)) {
            if (*(char *)(param_1 + 0x9daa1) == '\0') {
              if (3 < DebugLevel) {
                printk("%s: current total frame len = %d, pkt_len = %d, amsdu_limit_len_adjust = %d\n"
                       ,"check_amsdu_limit",*(undefined2 *)(param_3 + 6),piVar14[0x19],
                       *(undefined4 *)(iVar7 + 0xd0c));
              }
              if (*(uint *)(iVar7 + 0xd0c) < (uint)*(ushort *)(param_3 + 6) + piVar14[0x19])
              goto LAB_000d2d98;
            }
            else if (*(byte *)(param_1 + 0x9daa2) <= (byte)param_3[3]) goto LAB_000d2d98;
            goto LAB_000d2bf0;
          }
        }
LAB_000d2d98:
        *piVar14 = *(int *)(iVar10 + 0x2f6c4);
        *(int **)(iVar10 + 0x2f6c4) = piVar14;
        if (*(int *)(iVar10 + 0x2f6c8) == 0) {
          *(int **)(iVar10 + 0x2f6c8) = piVar14;
        }
        iVar10 = param_1 + uVar12 * 0x620;
        iVar9 = param_1 + (uVar11 + uVar12 * 0x62) * 0x10;
        *(int *)(iVar9 + 0x2f6cc) = *(int *)(iVar9 + 0x2f6cc) + 1;
        *(int *)(iVar10 + 0x2f714) = *(int *)(iVar10 + 0x2f714) + 1;
LAB_000d2f04:
        if (param_3[5] == '\x04') {
          iVar7 = *(int *)(param_3 + 0x48);
          goto LAB_000d2f14;
        }
        break;
      }
      uVar8 = *(uint *)(param_3 + 0x18);
      if (((uVar8 & 0x10000000) != 0) && (iVar9 = FUN_000cfd30(param_1,piVar14,param_3), iVar9 == 0)
         ) {
        *(uint *)(param_3 + 0x18) = uVar8 & 0xefffffff;
      }
LAB_000d2bf0:
      param_3[1] = bVar1;
      iVar9 = asic_check_hw_resource(param_1,uVar13,*param_3);
      if (iVar9 == 1) {
        hif_free_txd(param_1,*param_3);
        iVar9 = asic_check_hw_resource(param_1,uVar13,*param_3);
        if (iVar9 != 1) {
          asic_set_resource_state(param_1,*param_3,1);
          pci_dec_resource_full_cnt(param_1,*param_3);
          goto LAB_000d2c10;
        }
LAB_000d2e10:
        *piVar14 = *(int *)(iVar10 + 0x2f6c4);
        *(int **)(iVar10 + 0x2f6c4) = piVar14;
        if (*(int *)(iVar10 + 0x2f6c8) == 0) {
          *(int **)(iVar10 + 0x2f6c8) = piVar14;
        }
        iVar10 = param_1 + uVar12 * 0x620;
        iVar9 = param_1 + (uVar11 + uVar12 * 0x62) * 0x10;
        *(int *)(iVar9 + 0x2f6cc) = *(int *)(iVar9 + 0x2f6cc) + 1;
        *(int *)(iVar10 + 0x2f714) = *(int *)(iVar10 + 0x2f714) + 1;
        uVar2 = *(ushort *)(param_2 + 4);
        uVar8 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if ((uVar2 < uVar8) && (*(ushort *)(param_2 + 4) < 0x120)) {
          *(undefined1 *)(param_2 + uVar11 + 0x28) = 1;
        }
        else {
          *(undefined2 *)(param_2 + (uVar11 + 4) * 2 + 2) = 0;
        }
        goto LAB_000d2f04;
      }
LAB_000d2c10:
      if (iVar9 != 0) goto LAB_000d2e10;
      cVar3 = param_3[3];
      param_3[3] = cVar3 + '\x01';
      param_3[4] = *(char *)((int)piVar14 + 0x2b) + param_3[4];
      *(short *)(param_3 + 6) = (short)piVar14[0x19] + *(short *)(param_3 + 6);
      if ((char)(cVar3 + '\x01') == '\x01') {
        *(int **)(param_3 + 0xc) = piVar14;
        *(undefined4 *)(param_3 + 0x10) = uVar13;
        *(uint *)(param_3 + 8) = param_1 + 0x1c0 + uVar12 * 0x620 + 0x2f4e0;
        uVar5 = hif_get_tx_buf(*(undefined4 *)(param_1 + 0xa797a0),param_3,*param_3,param_3[5]);
        *(undefined4 *)(param_3 + 0x58) = uVar5;
      }
      *piVar14 = 0;
      if (*(undefined4 **)(param_3 + 0x44) == (undefined4 *)0x0) {
        *(int **)(param_3 + 0x40) = piVar14;
      }
      else {
        **(undefined4 **)(param_3 + 0x44) = piVar14;
      }
      *(int **)(param_3 + 0x44) = piVar14;
      iVar7 = *(int *)(param_3 + 0x48) + 1;
      *(int *)(param_3 + 0x48) = iVar7;
    }
    if (3 < DebugLevel) {
      printk("<--%s():pTxBlk.TxPktList.Num=%d, deq_info.pkt_cnt=%d\n","deq_packet_gatter",
             *(undefined4 *)(param_3 + 0x48),*(undefined4 *)(param_2 + 0x18));
    }
  }
  _raw_spin_unlock_bh(iVar6);
  if (*(int *)(param_3 + 0x48) != 0) {
    *(int *)(param_2 + 0x20) = *(int *)(param_2 + 0x20) + *(int *)(param_3 + 0x48);
  }
  return 0;
}

