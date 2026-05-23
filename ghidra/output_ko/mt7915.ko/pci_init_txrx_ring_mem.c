// module: mt7915.ko
// function: pci_init_txrx_ring_mem @ 0x1ce130
// size: 2844 bytes
//

undefined4 pci_init_txrx_ring_mem(undefined4 param_1)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  undefined4 uVar6;
  int *piVar7;
  code *pcVar8;
  undefined4 uVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined2 uVar14;
  int iVar15;
  byte bVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  uint uVar20;
  byte *pbVar21;
  undefined4 *puVar22;
  uint uVar23;
  uint uVar24;
  code *pcVar25;
  code *pcVar26;
  byte *pbVar27;
  uint *puVar28;
  undefined4 uVar29;
  uint uVar30;
  int iVar31;
  int iVar32;
  uint uVar33;
  uint uVar34;
  bool bVar35;
  uint local_48;
  undefined4 local_34;
  undefined4 local_30;
  byte local_2c;
  undefined4 *puVar13;
  
  pbVar1 = (byte *)hc_get_hif_ctrl();
  iVar2 = hc_get_hdev_privdata(param_1);
  iVar31 = *(int *)(pbVar1 + 0xa0);
  hc_get_ct_cb(param_1);
  hc_get_chip_cap(param_1);
  iVar3 = hc_get_chip_cap(param_1);
  pbVar4 = (byte *)hc_get_hif_ctrl(param_1);
  uVar5 = hc_get_asic_cap(param_1);
  chip_hif_chip_match(param_1);
  uVar6 = multi_hif_entry_gid_get(*(undefined4 *)(pbVar4 + 0xa0));
  multi_hif_entry_get_by_gid(uVar6,&local_30);
  uVar17 = 0;
  uVar23 = uVar17;
  puVar22 = local_30;
  if (local_30 != &local_30) {
    do {
      puVar22 = (undefined4 *)*puVar22;
      uVar17 = uVar17 + 1;
    } while (puVar22 != &local_30);
    uVar23 = uVar17 & 0xff;
    uVar17 = uVar23 << 2;
  }
  pbVar4[0xa8] = (byte)uVar23;
  os_alloc_mem(0,pbVar4 + 0xac,uVar17);
  iVar15 = *(int *)(pbVar4 + 0xac);
  if (iVar15 == 0) {
    uVar17 = (uint)pbVar4[0xa8];
LAB_001ce25c:
    bVar16 = 0;
    *pbVar4 = 0;
    pbVar4[1] = 0;
    if (uVar17 == 0) {
      iVar15 = 0;
    }
    else {
      piVar7 = (int *)(*(int *)(pbVar4 + 0xac) + -4);
      uVar23 = 0;
      do {
        piVar7 = piVar7 + 1;
        uVar24 = uVar23 + *(byte *)(*piVar7 + 0x10);
        uVar23 = uVar24 & 0xff;
        *pbVar4 = (byte)uVar24;
        bVar16 = bVar16 + *(char *)(*piVar7 + 0x11);
        pbVar4[1] = bVar16;
      } while (piVar7 != (int *)(*(int *)(pbVar4 + 0xac) + (uVar17 - 1 & 0xff) * 4));
      iVar15 = uVar23 << 2;
    }
  }
  else {
    if (&local_30 != local_30) {
      uVar17 = 0;
      puVar22 = local_30;
      while( true ) {
        uVar23 = uVar17 & 0xff;
        uVar17 = uVar17 + 1;
        *(undefined4 **)(iVar15 + uVar23 * 4) = puVar22 + 6;
        puVar22 = (undefined4 *)*puVar22;
        if (&local_30 == puVar22) break;
        iVar15 = *(int *)(pbVar4 + 0xac);
      }
    }
    if (pbVar4[0xa8] != 0) {
      uVar23 = 0;
      do {
        iVar15 = uVar23 * 4;
        uVar23 = uVar23 + 1 & 0xff;
        *(byte **)(*(int *)(*(int *)(pbVar4 + 0xac) + iVar15) + 0xd0) = pbVar4;
        uVar17 = (uint)pbVar4[0xa8];
      } while (uVar23 < uVar17);
      goto LAB_001ce25c;
    }
    *pbVar4 = 0;
    pbVar4[1] = 0;
    iVar15 = 0;
  }
  os_alloc_mem(0,pbVar4 + 8,iVar15);
  if (((*(int *)(pbVar4 + 8) != 0) &&
      (os_alloc_mem(0,pbVar4 + 4,(uint)pbVar4[1] << 2), *(int *)(pbVar4 + 4) != 0)) &&
     (pbVar4[0xa8] != 0)) {
    uVar23 = 0;
    uVar17 = 0;
    uVar24 = 0;
    do {
      iVar15 = *(int *)(*(int *)(pbVar4 + 0xac) + uVar24 * 4);
      if (*(char *)(iVar15 + 0x10) != '\0') {
        uVar18 = 0;
        do {
          iVar32 = uVar18 * 0x60;
          uVar18 = uVar18 + 1 & 0xff;
          *(char *)(*(int *)(iVar15 + 0x18) + iVar32 + 0x58) = (char)uVar17;
          *(int *)(*(int *)(pbVar4 + 8) + uVar17 * 4) = *(int *)(iVar15 + 0x18) + iVar32;
          uVar17 = uVar17 + 1 & 0xff;
        } while (uVar18 < *(byte *)(iVar15 + 0x10));
      }
      if (*(char *)(iVar15 + 0x11) != '\0') {
        uVar18 = 0;
        do {
          iVar32 = uVar18 * 0xa0;
          uVar18 = uVar18 + 1 & 0xff;
          *(char *)(*(int *)(iVar15 + 0x14) + iVar32 + 0x1c) = (char)uVar23;
          iVar19 = *(int *)(iVar15 + 0x14) + iVar32;
          if ((*(uint *)(iVar19 + 0x80) & 1) != 0) {
            *(short *)(pbVar4 + 0x98) = (short)uVar23;
            iVar19 = *(int *)(iVar15 + 0x14) + iVar32;
          }
          *(int *)(*(int *)(pbVar4 + 4) + uVar23 * 4) = iVar19;
          uVar23 = uVar23 + 1 & 0xff;
        } while (uVar18 < *(byte *)(iVar15 + 0x11));
      }
      uVar24 = uVar24 + 1 & 0xff;
    } while (uVar24 < pbVar4[0xa8]);
  }
  *(code **)(pbVar4 + 0x10) = pci_cmd_dma_done_handle;
  *(code **)(pbVar4 + 0xc) = pci_tx_dma_done_handle;
  *(code **)(pbVar4 + 0x14) = pci_cmd_dma_done_handle;
  *(code **)(pbVar4 + 0x18) = pci_fwdl_dma_done_handle;
  if (*(char *)(iVar3 + 0x15a) == '\0') {
    *(code **)(pbVar4 + 0x1c) = pci_rx_dma_done_handle;
  }
  else {
    *(code **)(pbVar4 + 0x1c) = pci_rx_dma_done_rxq_handle;
  }
  *(code **)(pbVar4 + 0x68) = pci_get_pkt_dynamic_page_io;
  bVar35 = *pbVar4 != 0;
  pcVar25 = pci_get_pkt_pre_slab_io;
  *(code **)(pbVar4 + 0x78) = pci_get_pkt_pre_slab_io;
  if (bVar35) {
    pcVar25 = *(code **)(pbVar4 + 8);
  }
  *(code **)(pbVar4 + 0x20) = pci_rx_event_dma_done_handle;
  *(code **)(pbVar4 + 100) = pci_get_pkt_dynamic_page_ddone;
  *(code **)(pbVar4 + 0x7c) = pci_get_pkt_dynamic_page_ddone_debug;
  *(code **)(pbVar4 + 0x80) = pci_get_pkt_dynamic_page_io_debug;
  pcVar8 = (code *)0x0;
  if (bVar35) {
    pcVar8 = pcVar25 + (uint)*pbVar4 * 4;
  }
  *(code **)(pbVar4 + 0x6c) = pci_get_pkt_dynamic_slab_ddone;
  *(code **)(pbVar4 + 0x70) = pci_get_pkt_dynamic_slab_io;
  *(code **)(pbVar4 + 0x74) = pci_get_pkt_pre_slab_ddone;
  if (bVar35) {
    do {
      pcVar26 = pcVar25 + 4;
      piVar7 = *(int **)pcVar25;
      if (*piVar7 == 1) {
        *(int **)(pbVar4 + 0x88) = piVar7;
      }
      else if (*piVar7 == 3) {
        *(int **)(pbVar4 + 0x8c) = piVar7;
      }
      pcVar25 = pcVar26;
    } while (pcVar26 != pcVar8);
  }
  uVar17 = (uint)pbVar4[1];
  if (uVar17 != 0) {
    iVar15 = 0;
    do {
      piVar7 = *(int **)(*(int *)(pbVar4 + 4) + iVar15 * 4);
      iVar15 = iVar15 + 1;
      if (((uVar5 & 0x2000) != 0) && (*piVar7 == 5)) {
        *(undefined1 *)((int)piVar7 + 0x1f) = 1;
        uVar17 = (uint)pbVar4[1];
      }
    } while (iVar15 < (int)uVar17);
  }
  puVar22 = (undefined4 *)(*(byte *)(iVar3 + 0x158) & 0xfd);
  if ((*(byte *)(iVar3 + 0x158) & 0xfd) == 0) {
    local_2c = (byte)puVar22;
    bVar16 = *pbVar4;
    local_30 = puVar22;
    if (bVar16 != 0) {
      puVar11 = *(undefined4 **)(pbVar4 + 8);
      puVar12 = puVar11;
      do {
        puVar13 = puVar12 + 1;
        bVar35 = puVar22 == (undefined4 *)&DAT_00000004;
        if (puVar22 < &DAT_00000005) {
          bVar35 = *(int *)*puVar12 == 0;
        }
        if (bVar35) {
          *(char *)((int)&local_30 + (int)puVar22) = (char)((int *)*puVar12)[0x16];
          puVar22 = (undefined4 *)((uint)((int)puVar22 + 1) & 0xff);
        }
        puVar12 = puVar13;
      } while (puVar13 != puVar11 + bVar16);
      if (puVar22 == (undefined4 *)&DAT_00000005) {
        pbVar27 = pbVar4;
LAB_001cea84:
        iVar15 = 1;
        pbVar21 = pbVar27;
        do {
          switch(iVar15) {
          case 1:
            pbVar27[0x24] = (byte)local_30;
            pbVar27[0x25] = local_30._1_1_;
            pbVar27[0x26] = local_30._2_1_;
            pbVar27[0x27] = local_30._3_1_;
            break;
          case 2:
            pbVar27[0x28] = (byte)local_30;
            pbVar27[0x29] = local_30._1_1_;
            pbVar27[0x2a] = local_30._2_1_;
            pbVar27[0x2b] = local_30._3_1_;
            break;
          case 3:
            pbVar27[0x2c] = local_30._1_1_;
            pbVar27[0x2d] = local_30._1_1_;
            pbVar27[0x2e] = local_30._1_1_;
            pbVar27[0x2f] = local_30._1_1_;
            break;
          case 4:
            pbVar27[0x30] = local_2c;
            pbVar27[0x31] = local_2c;
            pbVar27[0x32] = local_2c;
            pbVar27[0x33] = local_2c;
            break;
          default:
            pbVar21[0x24] = 0;
            pbVar21[0x25] = 0;
            pbVar21[0x26] = 0;
            pbVar21[0x27] = 0;
            if (iVar15 == 8) goto code_r0x001ceb9c;
          }
          iVar15 = iVar15 + 1;
          pbVar21 = pbVar21 + 4;
        } while( true );
      }
    }
    goto LAB_001ce590;
  }
LAB_001ce510:
  local_30 = (undefined4 *)((uint)local_30 & 0xffff0000);
  bVar16 = *pbVar4;
  iVar3 = RtmpOsGetNetDevPriv(*(undefined4 *)(pbVar4 + 0xb0));
  if (bVar16 == 0) {
    chip_hif_pci_data_ring_assign(*(undefined4 *)(iVar3 + 0xa797a0),&local_30);
  }
  else {
    puVar12 = *(undefined4 **)(pbVar4 + 8) + bVar16;
    puVar22 = *(undefined4 **)(pbVar4 + 8);
    uVar17 = 0;
    do {
      while( true ) {
        puVar11 = puVar22 + 1;
        bVar35 = uVar17 == 1;
        if (uVar17 < 2) {
          bVar35 = *(int *)*puVar22 == 0;
        }
        if (!bVar35) break;
        uVar23 = uVar17 + 1 & 0xff;
        *(char *)((int)&local_30 + uVar17) = (char)((int *)*puVar22)[0x16];
        puVar22 = puVar11;
        uVar17 = uVar23;
        if (puVar11 == puVar12) goto LAB_001ce574;
      }
      puVar22 = puVar11;
    } while (puVar11 != puVar12);
LAB_001ce574:
    chip_hif_pci_data_ring_assign(*(undefined4 *)(iVar3 + 0xa797a0),&local_30);
    if (uVar17 == 2) {
      pbVar27 = pbVar4;
      do {
        pbVar27[0x24] = (byte)local_30;
        pbVar21 = pbVar27 + 4;
        pbVar27[0x25] = (byte)local_30;
        pbVar27[0x26] = (byte)local_30;
        pbVar27[0x27] = (byte)local_30;
        pbVar27 = pbVar21;
      } while (pbVar21 != pbVar4 + 0x20);
      pbVar27 = pbVar4 + 0x20;
      do {
        pbVar27[0x24] = local_30._1_1_;
        pbVar21 = pbVar27 + 4;
        pbVar27[0x25] = local_30._1_1_;
        pbVar27[0x26] = local_30._1_1_;
        pbVar27[0x27] = local_30._1_1_;
        pbVar27 = pbVar21;
      } while (pbVar21 != pbVar4 + 0x40);
    }
  }
LAB_001ce590:
  uVar17 = (uint)*pbVar1;
  uVar23 = (uint)pbVar1[1];
  uVar6 = *(undefined4 *)(iVar31 + 0xcc);
  if (uVar17 != 0) {
    uVar5 = 0;
    do {
      puVar28 = *(uint **)(*(int *)(pbVar1 + 8) + uVar5 * 4);
      uVar24 = (uint)*(ushort *)((int)puVar28 + 0x5a);
      if (*puVar28 == 0) {
        uVar18 = puVar28[0x10];
        if (puVar28[0xf] != 0) {
          __memzero();
          uVar18 = puVar28[0x10];
        }
        uVar30 = puVar28[0x13];
        uVar33 = puVar28[0x11];
        if (puVar28[0x12] != 0) {
          __memzero();
          uVar30 = puVar28[0x13];
        }
        if (uVar24 != 0) {
          iVar3 = 0;
          uVar34 = 0;
          uVar10 = uVar18;
          do {
            uVar20 = puVar28[3];
            uVar34 = uVar34 + 1;
            iVar15 = uVar20 + iVar3;
            *(undefined4 *)(iVar15 + 0xc) = 0;
            *(undefined4 *)(iVar15 + 0x10) = 0;
            *(undefined4 *)(uVar20 + iVar3) = 0x10;
            iVar3 = iVar3 + 0x24;
            *(uint *)(iVar15 + 4) = uVar10;
            *(uint *)(iVar15 + 8) = uVar10 + (uVar33 - uVar18);
            uVar29 = *(undefined4 *)(iVar31 + 0x6c4);
            *(uint *)(iVar15 + 0x1c) = uVar30;
            *(undefined4 *)(iVar15 + 0x18) = uVar29;
            *(byte *)(uVar10 + 7) = *(byte *)(uVar10 + 7) & 0x7f;
            uVar30 = uVar30 + *(int *)(iVar15 + 0x18);
            uVar10 = uVar10 + 0x10;
          } while (uVar34 != uVar24);
        }
        puVar28[8] = 0;
        puVar28[5] = 1;
        iVar3 = DebugLevel;
        puVar28[6] = 5;
        puVar28[7] = 0xf;
        if (-1 < iVar3) {
          printk("TxRing[%d]: attr:%d, total %d entry initialized\n",uVar5,*puVar28,uVar24);
        }
      }
      else {
        if (3 < *puVar28) {
          if (-1 < DebugLevel) {
            printk("TxRing[%d]: wrong attr:%d\n",uVar5);
          }
          return 2;
        }
        uVar18 = puVar28[0x11];
        uVar30 = puVar28[0x10];
        if (puVar28[0xf] != 0) {
          __memzero(uVar30);
        }
        if (uVar24 != 0) {
          iVar3 = 0;
          uVar10 = 0;
          uVar33 = uVar30;
          do {
            uVar34 = puVar28[3];
            uVar10 = uVar10 + 1;
            iVar15 = uVar34 + iVar3;
            *(undefined4 *)(iVar15 + 0xc) = 0;
            *(undefined4 *)(iVar15 + 0x10) = 0;
            *(undefined4 *)(uVar34 + iVar3) = 0x10;
            iVar3 = iVar3 + 0x24;
            *(uint *)(iVar15 + 4) = uVar33;
            *(uint *)(iVar15 + 8) = uVar33 + (uVar18 - uVar30);
            *(byte *)(uVar33 + 7) = *(byte *)(uVar33 + 7) | 0x80;
            uVar33 = uVar33 + 0x10;
          } while (uVar10 != uVar24);
        }
        puVar28[4] = 0;
        puVar28[10] = 0;
        if (2 < DebugLevel) {
          printk("ring_attr:%d, total %d entry initialized\n",*puVar28,uVar24);
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 != uVar17);
  }
  iVar3 = *(int *)(pbVar1 + 0xa4);
  if (uVar23 == 0) {
    local_34 = 0;
  }
  else {
    local_34 = 0;
    local_48 = 0;
    do {
      piVar7 = *(int **)(*(int *)(pbVar1 + 4) + local_48 * 4);
      iVar31 = piVar7[0x17];
      iVar15 = *piVar7;
      if (piVar7[0x16] != 0) {
        __memzero();
        iVar31 = piVar7[0x17];
      }
      if (0 < DebugLevel) {
        printk("RX[%d] DESC %p size = %lu\n",local_48,iVar31,piVar7[0x16]);
        iVar31 = piVar7[0x17];
      }
      if (iVar15 - 4U < 2) {
        uVar29 = 0x6a4;
      }
      else {
        uVar29 = 0;
      }
      if ((iVar3 == 0) || ((char)piVar7[0xe] != '\x02')) {
        uVar5 = (uint)*(ushort *)(piVar7 + 5);
        if (uVar5 != 0) goto LAB_001ce7a8;
      }
      else {
        uVar5 = 10;
        *(undefined2 *)(piVar7 + 5) = 10;
LAB_001ce7a8:
        iVar32 = piVar7[0x18] - iVar31;
        iVar15 = 0;
        do {
          iVar19 = piVar7[6] + iVar15 * 0x24;
          *(undefined4 *)(piVar7[6] + iVar15 * 0x24) = 0x10;
          *(int *)(iVar19 + 4) = iVar31;
          *(int *)(iVar19 + 8) = iVar31 + iVar32;
          *(undefined4 *)(iVar19 + 0x18) = uVar29;
          iVar15 = iVar15 + 1;
          iVar31 = iVar31 + 0x10;
          uVar9 = RTMP_AllocateRxPacketBuffer(piVar7,uVar6,uVar29,iVar19 + 0x1c,iVar19 + 0x20);
          *(undefined4 *)(iVar19 + 0xc) = uVar9;
          if (*(int *)(iVar19 + 0x1c) == 0) {
            if (DebugLevel < 0) {
              local_34 = 3;
            }
            else {
              local_34 = 3;
              printk("Failed to allocate RxRing\'s 1st buffer\n");
            }
            break;
          }
          puVar22 = *(undefined4 **)(iVar19 + 4);
          *puVar22 = *(undefined4 *)(iVar19 + 0x20);
          *(char *)((int)puVar22 + 6) = (char)uVar29;
          *(byte *)((int)puVar22 + 7) =
               *(byte *)((int)puVar22 + 7) & 0x40 | (byte)((uint)uVar29 >> 8);
        } while (iVar15 < (int)uVar5);
      }
      local_48 = local_48 + 1;
    } while (local_48 != uVar23);
  }
  __memzero(&DAT_002963b0 + iVar2,0x20);
  iVar3 = RTMP_AllocateFragPacketBuffer(iVar2,0xf00);
  *(int *)(&DAT_002963b0 + iVar2) = iVar3;
  if (iVar3 == 0) {
    local_34 = 3;
  }
  if (uVar17 != 0) {
    uVar5 = 0;
    do {
      iVar3 = *(int *)(*(int *)(pbVar1 + 8) + uVar5 * 4);
      uVar5 = uVar5 + 1;
      *(undefined4 *)(iVar3 + 0x10) = 0;
      *(undefined4 *)(iVar3 + 0x28) = 0;
    } while (uVar5 != uVar17);
  }
  if (uVar23 != 0) {
    uVar17 = 0;
    do {
      piVar7 = *(int **)(*(int *)(pbVar1 + 4) + uVar17 * 4);
      uVar17 = uVar17 + 1;
      piVar7[4] = 0;
      piVar7[0xd] = *(ushort *)(piVar7 + 5) - 1;
      if (*piVar7 - 4U < 2) {
        uVar14 = 0x6a4;
      }
      else {
        uVar14 = 0;
      }
      *(undefined2 *)((int)piVar7 + 0x2e) = uVar14;
    } while (uVar17 != uVar23);
  }
  *(undefined4 *)(iVar2 + 0xa39f10) = 0;
  return local_34;
code_r0x001ceb9c:
  pbVar27 = pbVar27 + 0x20;
  if (pbVar27 == pbVar4 + 0x40) goto code_r0x001cebac;
  goto LAB_001cea84;
code_r0x001cebac:
  if ((*(byte *)(iVar3 + 0x158) & 0xfd) == 0) goto LAB_001ce590;
  goto LAB_001ce510;
}

