// module: mt7915.ko
// function: pci_reset_txrx_ring_mem @ 0x1cc664
// size: 1080 bytes
//

void pci_reset_txrx_ring_mem(undefined4 param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  int *piVar5;
  short sVar6;
  undefined4 uVar7;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  int *piVar15;
  uint uVar16;
  int iVar17;
  undefined8 uVar18;
  uint local_44;
  
  pbVar4 = (byte *)hc_get_hif_ctrl();
  bVar1 = *pbVar4;
  bVar2 = pbVar4[1];
  uVar18 = hc_get_hdev_privdata(param_1);
  uVar7 = (undefined4)((ulonglong)uVar18 >> 0x20);
  piVar5 = (int *)uVar18;
  if (bVar1 != 0) {
    local_44 = 0;
    do {
      piVar15 = *(int **)(*(int *)(pbVar4 + 8) + local_44 * 4);
      uVar16 = (uint)*(ushort *)((int)piVar15 + 0x5a);
      if (uVar16 != 0) {
        uVar13 = 0;
        uVar9 = uVar13;
        do {
          iVar8 = piVar15[3] + uVar13;
          puVar11 = *(undefined4 **)(iVar8 + 4);
          if (*(int *)(iVar8 + 0x18) != 0) {
            linux_pci_unmap_single
                      (*(undefined4 *)(*piVar5 + 0xc),*(undefined4 *)(iVar8 + 0x20),
                       *(int *)(iVar8 + 0x18),0xff00);
          }
          iVar12 = *(int *)(iVar8 + 0xc);
          if (iVar12 != 0) {
            if (*piVar15 == 0) {
              linux_pci_unmap_single
                        (*(undefined4 *)(*piVar5 + 0xc),*(undefined4 *)(iVar8 + 0x14),
                         *(undefined4 *)(iVar12 + 100),0xff00);
            }
            else if (*piVar15 - 1U < 2) {
              bVar3 = *(byte *)((int)puVar11 + 7);
              *(byte *)((int)puVar11 + 7) = bVar3 & 0x7f;
              linux_pci_unmap_single
                        (*(undefined4 *)(*piVar5 + 0xc),*puVar11,
                         (uint)*(byte *)((int)puVar11 + 6) | (bVar3 & 0x3f) << 8,0xff00);
            }
            else if (-1 < DebugLevel) {
              printk("%s: ring_attr:%d, specific handle is needed?\n","pci_reset_txrx_ring_mem");
            }
            RTMPFreeNdisPacket(piVar5,iVar12);
          }
          iVar12 = *(int *)(iVar8 + 0x10);
          *(undefined4 *)(iVar8 + 0xc) = 0;
          if (iVar12 != 0) {
            linux_pci_unmap_single
                      (*(undefined4 *)(*piVar5 + 0xc),puVar11[2],
                       (uint)*(byte *)(puVar11 + 1) | (*(byte *)((int)puVar11 + 5) & 0x3f) << 8,
                       0xff00);
            RTMPFreeNdisPacket(piVar5,iVar12);
          }
          uVar9 = uVar9 + 1;
          uVar13 = uVar13 + 0x24;
          *(undefined4 *)(iVar8 + 0x10) = 0;
        } while (uVar9 != uVar16);
      }
      uVar7 = 0;
      if (uVar16 * 0x24 != 0) {
        __memzero(piVar15[3]);
        uVar7 = extraout_r1_02;
      }
      local_44 = local_44 + 1;
    } while (local_44 != bVar1);
  }
  if (bVar2 != 0) {
    uVar16 = 0;
    do {
      piVar15 = *(int **)(*(int *)(pbVar4 + 4) + uVar16 * 4);
      uVar9 = (uint)*(ushort *)(piVar15 + 5);
      iVar8 = *piVar15;
      iVar12 = uVar9 - 1;
      if (uVar9 != 0) {
        iVar14 = iVar12 * 0x24;
        do {
          while( true ) {
            hc_get_chip_cap(param_1,uVar7);
            iVar10 = piVar15[6] + iVar14;
            iVar17 = *(int *)(iVar10 + 0xc);
            uVar7 = *(undefined4 *)(iVar10 + 0x20);
            if ((iVar17 != 0 && *(int *)(iVar10 + 0x1c) != 0) &&
               (linux_pci_unmap_single
                          (*(undefined4 *)(*piVar5 + 0xc),uVar7,*(undefined4 *)(iVar10 + 0x18),
                           0xff01), uVar7 = extraout_r1, iVar8 == 4)) break;
LAB_001cc858:
            iVar12 = iVar12 + -1;
            iVar14 = iVar14 + -0x24;
            if (iVar12 == -1) goto LAB_001cc910;
          }
          uVar13 = iVar17 + 0x40000000U >> 0xc;
          if (0x1000 < (*(int *)(iVar10 + 0x18) + 0x3fU & 0xffffffe0) + 0xc0) {
            os_free_mem(iVar17);
            uVar7 = extraout_r1_03;
            goto LAB_001cc858;
          }
          iVar12 = iVar12 + -1;
          iVar14 = iVar14 + -0x24;
          iVar10 = mem_map + uVar13 * 0x20;
          g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
          if ((*(uint *)(mem_map + uVar13 * 0x20) & 0x8000) != 0) {
            iVar10 = *(int *)(iVar10 + 0x1c);
          }
          put_page(iVar10);
          uVar7 = extraout_r1_00;
        } while (iVar12 != -1);
      }
LAB_001cc910:
      if (iVar8 == 5) {
        iVar8 = hc_get_hif_ctrl(param_1);
        iVar12 = 0;
        iVar8 = *(int *)(*(int *)(iVar8 + 4) + uVar16 * 4);
        *(undefined2 *)(iVar8 + 0x20) = 0;
        sVar6 = *(short *)(iVar8 + 0x14) + 1;
        *(undefined2 *)(iVar8 + 0x22) = 0;
        *(short *)(iVar8 + 0x24) = sVar6;
        if (sVar6 == 0) {
          *(undefined2 *)(iVar8 + 0x40) = 0;
          *(undefined2 *)(iVar8 + 0x42) = 0;
          *(undefined2 *)(iVar8 + 0x44) = 1;
        }
        else {
          uVar13 = 0;
          do {
            uVar13 = uVar13 + 1;
            *(undefined4 *)(*(int *)(iVar8 + 0x28) + iVar12) = 0x6a4;
            iVar12 = iVar12 + 0xc;
          } while (uVar13 < *(ushort *)(iVar8 + 0x24));
          *(undefined2 *)(iVar8 + 0x40) = 0;
          *(undefined2 *)(iVar8 + 0x42) = 0;
          *(undefined2 *)(iVar8 + 0x44) = 1;
        }
        iVar12 = 0;
        uVar13 = 0;
        do {
          uVar13 = uVar13 + 1;
          *(undefined4 *)(*(int *)(iVar8 + 0x48) + iVar12) = 0x10000;
          iVar12 = iVar12 + 0xc;
        } while (uVar13 < *(ushort *)(iVar8 + 0x44));
      }
      uVar7 = 0;
      if (uVar9 * 0x24 != 0) {
        __memzero(piVar15[6]);
        uVar7 = extraout_r1_01;
      }
      uVar16 = uVar16 + 1;
    } while (uVar16 != bVar2);
  }
  if (piVar5[0xa58ec] != 0) {
    RTMPFreeNdisPacket(piVar5);
    piVar5[0xa58ec] = 0;
  }
  os_free_mem(*(undefined4 *)(pbVar4 + 8));
  os_free_mem(*(undefined4 *)(pbVar4 + 4));
  os_free_mem(*(undefined4 *)(pbVar4 + 0xac));
  return;
}

