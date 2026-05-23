// module: plat-zxylzb_9128S.ko
// function: pp_net_tcp_gso_tx_upload @ 0x19ac4
// size: 1904 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 pp_net_tcp_gso_tx_upload(int param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  ushort uVar4;
  bool bVar5;
  bool bVar6;
  code *pcVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  undefined4 uVar11;
  int iVar12;
  uint uVar13;
  byte *pbVar14;
  size_t __n;
  size_t sVar15;
  uint *puVar16;
  uint uVar17;
  byte bVar18;
  int iVar19;
  void *__dest;
  uint *puVar20;
  int iVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  bool bVar25;
  bool bVar26;
  uint local_70;
  uint local_6c;
  uint local_64;
  int local_54;
  uint local_2c [2];
  
  iVar12 = *(int *)(param_1 + 0xd4);
  iVar19 = *(int *)(param_1 + 0xd0) + (uint)*(ushort *)(param_1 + 0xae);
  if (*(short *)(iVar12 + 0xc) == 0x81) {
    if ((*(short *)(iVar12 + 0x10) + 0x9c78U & 0xfeff) == 0) {
      pbVar14 = (byte *)(iVar12 + 0x1a);
    }
    else {
      pbVar14 = (byte *)(iVar12 + 0x12);
    }
  }
  else if ((*(short *)(iVar12 + 0xc) + 0x9c78U & 0xfeff) == 0) {
    pbVar14 = (byte *)(iVar12 + 0x16);
  }
  else {
    pbVar14 = (byte *)(iVar12 + 0xe);
  }
  uVar2 = (uint)(*pbVar14 >> 4);
  if (uVar2 == 6) {
    local_54 = (iVar19 + -0x28) - iVar12;
    pp_gso_tx._36_4_ = pp_gso_tx._36_4_ + 1;
  }
  else {
    local_54 = (iVar19 + -0x14) - iVar12;
    pp_gso_tx._32_4_ = pp_gso_tx._32_4_ + 1;
  }
  bVar3 = *(byte *)(iVar19 + 0xd);
  iVar21 = *(int *)(param_1 + 100);
  uVar9 = *(uint *)(iVar19 + 4);
  iVar1 = (uint)(*(byte *)(iVar19 + 0xc) >> 4) * 4;
  __n = (iVar19 - iVar12) + iVar1;
  pp_gso_tx._40_4_ = uVar2;
  *(byte *)(iVar19 + 0xd) = bVar3 & 0xf7;
  local_70 = iVar21 - __n;
  sVar15 = __n;
  iVar12 = iVar19 - iVar12;
  if (0x15 < local_54) {
    sVar15 = 0x6488;
    iVar12 = local_54;
  }
  local_64 = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
             uVar9 >> 0x18;
  if (local_54 < 0x16) {
    bVar5 = false;
  }
  else {
    bVar5 = *(ushort *)(*(int *)(param_1 + 0xd4) + iVar12 + -10) == sVar15;
  }
  if (*(short *)(*(int *)(param_1 + 0xcc) + 2) == 0) {
    *(short *)(*(int *)(param_1 + 0xcc) + 2) = 0x5ea - (short)__n;
  }
  if (0 < (int)local_70) {
    iVar12 = param_3 * 0x1c;
    do {
      pbVar14 = (byte *)pon_tm_get_next_txdesc(param_3);
      if (pbVar14 == (byte *)0x0) {
        printk("gso get tx desc  failed\n");
        return 0;
      }
      if (pp_gso_bp_cnt == 0) {
        local_6c = pon_tm_bmu_alloc_bp();
        if ((int)local_6c < 0) {
          iVar12 = (param_3 & 0xff) * 0x1c;
          if (*(int *)(net_txq + iVar12 + 0xc) == 0) {
            iVar19 = 0x3ff;
          }
          else {
            iVar19 = *(int *)(net_txq + iVar12 + 0xc) + -1;
          }
          *(int *)(net_txq + iVar12 + 0xc) = iVar19;
          printk("alloc bp failed\n");
          return 0;
        }
        __dest = (void *)(u32_BP_SIZE * local_6c +
                         pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000);
        pp_gso_tx._16_4_ = pp_gso_tx._16_4_ + 1;
        __memzero((int)__dest + __n,0x5dc);
        bVar6 = false;
      }
      else {
        iVar19 = pp_gso_bp_idx * 4;
        pp_gso_bp_idx = pp_gso_bp_idx + 1 & 0x3ff;
        local_6c = *(uint *)(pp_gso_bp_pool + iVar19);
        __dest = (void *)(u32_BP_SIZE * local_6c +
                         pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000);
        bVar6 = true;
      }
      memcpy(__dest,*(void **)(param_1 + 0xd4),__n);
      uVar17 = (uint)*(ushort *)(*(int *)(param_1 + 0xcc) + 2);
      iVar19 = (int)__dest +
               ((*(int *)(param_1 + 0xd0) + (uint)*(ushort *)(param_1 + 0xae)) -
               *(int *)(param_1 + 0xd4));
      *(uint *)(iVar19 + 4) =
           local_64 << 0x18 | (local_64 >> 8 & 0xff) << 0x10 | (local_64 >> 0x10 & 0xff) << 8 |
           local_64 >> 0x18;
      uVar9 = local_70;
      if ((int)uVar17 <= (int)local_70) {
        uVar9 = uVar17;
      }
      local_70 = local_70 - uVar9;
      local_64 = local_64 + uVar9;
      if (local_70 == 0) {
        *(byte *)(iVar19 + 0xd) =
             *(byte *)(iVar19 + 0xd) & 0xf7 | (byte)((((uint)bVar3 << 0x1c) >> 0x1f) << 3);
        if (uVar2 == 6) goto LAB_0001a094;
LAB_00019c40:
        puVar20 = (uint *)((int)__dest + local_54);
        uVar17 = (__n - local_54) + uVar9;
        *(ushort *)((int)puVar20 + 2) =
             (ushort)((uVar17 & 0xff) << 8) | (ushort)(uVar17 >> 8) & 0xff;
        *(undefined2 *)(iVar19 + 0x10) = 0;
        uVar22 = puVar20[3];
        uVar4 = *(ushort *)((int)puVar20 + 2);
        uVar17 = *puVar20;
        uVar23 = puVar20[4];
        uVar10 = csum_partial(iVar19,(uint)(*(byte *)(iVar19 + 0xc) >> 4) << 2,0);
        uVar17 = ((uVar4 & 0xff) << 8 | (uint)(uVar4 >> 8)) + ((byte)uVar17 & 0xf) * -4 & 0xffff;
        uVar24 = uVar10 + uVar23;
        bVar25 = CARRY4(uVar24,uVar22) || CARRY4(uVar24 + uVar22,(uint)CARRY4(uVar10,uVar23));
        uVar10 = uVar24 + uVar22 + (uint)CARRY4(uVar10,uVar23);
        uVar17 = (uVar17 | 0x60000) >> 8 | uVar17 << 0x18;
        uVar17 = uVar10 + uVar17 + (uint)bVar25 +
                 (uint)(CARRY4(uVar10,uVar17) || CARRY4(uVar10 + uVar17,(uint)bVar25));
        *(ushort *)(iVar19 + 0x10) = ~(ushort)(uVar17 + (uVar17 >> 0x10 | uVar17 * 0x10000) >> 0x10)
        ;
        uVar17 = *puVar20;
        ((byte *)((int)puVar20 + 10))[0] = 0;
        ((byte *)((int)puVar20 + 10))[1] = 0;
        uVar23 = *puVar20;
        uVar10 = puVar20[1];
        bVar18 = ((byte)uVar17 & 0xf) - 5;
        uVar24 = uVar23 + uVar10;
        uVar17 = puVar20[2];
        uVar13 = uVar24 + uVar17 + (uint)CARRY4(uVar23,uVar10);
        uVar22 = puVar20[3];
        puVar16 = puVar20 + 4;
        bVar25 = CARRY4(uVar24,uVar17) || CARRY4(uVar24 + uVar17,(uint)CARRY4(uVar23,uVar10));
        while( true ) {
          bVar26 = CARRY4(uVar13,uVar22) || CARRY4(uVar13 + uVar22,(uint)bVar25);
          uVar13 = uVar13 + uVar22 + (uint)bVar25;
          uVar22 = *puVar16;
          if ((bVar18 & 0xf) == 0) break;
          bVar18 = bVar18 - 1;
          puVar16 = puVar16 + 1;
          bVar25 = bVar26;
        }
        uVar17 = uVar13 + uVar22 + (uint)bVar26 +
                 (uint)(CARRY4(uVar13,uVar22) || CARRY4(uVar13 + uVar22,(uint)bVar26));
        *(ushort *)((int)puVar20 + 10) =
             ~(ushort)(uVar17 + (uVar17 >> 0x10 | uVar17 * 0x10000) >> 0x10);
      }
      else {
        if (uVar2 != 6) goto LAB_00019c40;
LAB_0001a094:
        uVar17 = uVar9 + iVar1;
        *(ushort *)((int)__dest + local_54 + 4) =
             (ushort)((uVar17 & 0xff) << 8) | (ushort)(uVar17 >> 8) & 0xff;
        *(undefined2 *)(iVar19 + 0x10) = 0;
        uVar4 = *(ushort *)((int)__dest + local_54 + 4);
        uVar11 = csum_partial(iVar19,(uint)(*(byte *)(iVar19 + 0xc) >> 4) << 2,0);
        uVar17 = __csum_ipv6_magic((int)__dest + local_54 + 8,(int)__dest + local_54 + 0x18,
                                   (uint)(uVar4 >> 8) << 0x18 | (uVar4 & 0xff) << 0x10,0x6000000,
                                   uVar11);
        *(ushort *)(iVar19 + 0x10) = ~(ushort)(uVar17 + (uVar17 >> 0x10 | uVar17 << 0x10) >> 0x10);
      }
      if (bVar5) {
        uVar17 = (2 - local_54) + __n + uVar9;
        *(ushort *)((int)__dest + local_54 + -4) =
             (ushort)((uVar17 & 0xff) << 8) | (ushort)(uVar17 >> 8) & 0xff;
      }
      sVar15 = __n;
      if (pp_gso_bp_cnt == 0) {
        sVar15 = __n + uVar9;
      }
      uVar9 = __n + uVar9;
      pbVar14[0] = 0x80;
      pbVar14[1] = 0;
      pbVar14[2] = 0;
      pbVar14[3] = 0;
      pbVar14[4] = 0;
      pbVar14[5] = 0;
      pbVar14[6] = 1;
      pbVar14[7] = 0;
      pbVar14[8] = 0;
      pbVar14[9] = 0;
      pbVar14[10] = 0;
      pbVar14[0xb] = 1;
      if (param_3 == 0) {
        pbVar14[0xc] = 0;
        pbVar14[0xd] = 0;
        pbVar14[0xe] = 0;
        pbVar14[0xf] = 0;
        *pbVar14 = *pbVar14 & 0x80 | 0x49;
        local_2c[0] = param_3;
        if (dev_qos_get_queue != (code *)0x0) {
          (*dev_qos_get_queue)(*(undefined4 *)(param_1 + 0x84),local_2c);
        }
        pcVar7 = dev_qos_select_queue;
        if (lan_up == 1) {
          pbVar14[4] = 0;
          pbVar14[5] = 0;
          if (pcVar7 == (code *)0x0) {
            pbVar14[3] = pbVar14[3] & 0x1f;
          }
          else {
            cVar8 = (*pcVar7)(param_1,*(undefined4 *)(param_1 + 0x18));
            pbVar14[3] = pbVar14[3] & 0x1f | cVar8 << 5;
          }
          *(ushort *)(pbVar14 + 2) =
               *(ushort *)(pbVar14 + 2) & 0xfc0f | (ushort)((lan_up_port + 0x28U & 0x3f) << 4);
        }
        if ((int)uVar9 < 0x40) {
          uVar17 = 0x40;
          uVar9 = uVar17;
        }
        else {
          uVar17 = uVar9 & 0x3fff;
        }
      }
      else {
        pbVar14[0xc] = 3;
        pbVar14[0xd] = 0;
        pbVar14[0xe] = 0;
        pbVar14[0xf] = 0;
        uVar17 = uVar9 & 0x3fff;
        *(ushort *)(pbVar14 + 2) =
             *(ushort *)(pbVar14 + 2) & 0xfc0f | (*(byte *)(param_1 + 0xbc) + 0x28 & 0x3f) << 4;
      }
      pbVar14[8] = (byte)((int)local_6c >> 7);
      pbVar14[0xb] = pbVar14[0xb] & 1 | 0x20;
      uVar10 = *(ushort *)(pbVar14 + 0xc) & 0xffff0003 | uVar17 << 2;
      *(short *)(pbVar14 + 0xc) = (short)uVar10;
      if (bVar6) {
        uVar10 = (uint)pbVar14[6];
      }
      bVar18 = (byte)uVar10;
      *(uint *)(pbVar14 + 8) = *(uint *)(pbVar14 + 8) & 0xff8001ff | uVar17 << 9;
      if (bVar6) {
        bVar18 = bVar18 | 2;
      }
      if (bVar6) {
        pbVar14[6] = bVar18;
      }
      pbVar14[7] = pbVar14[7] & 1 | (byte)((local_6c & 0x7f) << 1);
      iVar21 = u32_BP_SIZE * local_6c + pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000
      ;
      *(int *)(net_txq + iVar12 + 0x10) = *(int *)(net_txq + iVar12 + 0x10) + 1;
      dma_cache_maint(iVar21,sVar15);
      soft_insert_tx_1desc(pbVar14,param_3);
      iVar19 = pp_gso_debug;
      *(int *)(net_txq + iVar12 + 0x18) = *(int *)(net_txq + iVar12 + 0x18) + 1;
      pp_gso_tx._4_4_ = pp_gso_tx._4_4_ + 1;
      if (0 < iVar19) {
        printk("gso tx len %u  BP %d ,addr %x\n",uVar9,local_6c,iVar21);
        dump_desc_tx(pbVar14);
        dump_net_data(iVar21,uVar9);
      }
      pp_gso_tx._8_4_ = uVar9 + pp_gso_tx._8_4_;
    } while (0 < (int)local_70);
  }
  return 0;
}

