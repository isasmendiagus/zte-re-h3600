// module: mt7915.ko
// function: pci_hif_chip_init @ 0x1d0850
// size: 2324 bytes
//

undefined4 pci_hif_chip_init(int *param_1,undefined4 *param_2)

{
  uint *puVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  byte bVar5;
  byte bVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  int iVar10;
  undefined1 *puVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
  undefined4 *puVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  int *piVar22;
  int iVar23;
  int iVar24;
  uint uVar25;
  uint uVar26;
  undefined4 uVar27;
  undefined4 uVar28;
  undefined4 uVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  uint local_60;
  int local_34;
  int local_30;
  int local_2c [2];
  
  local_30 = hif_ctrl_init(&local_34,5);
  if (local_30 != 0) {
    return 3;
  }
  *(undefined4 *)(local_34 + 0xbc) = param_2[4];
  hif_chip_init(local_34,param_2[1]);
  iVar15 = local_34;
  uVar25 = (uint)*(byte *)(local_34 + 0x10);
  *(undefined4 *)(local_34 + 0xcc) = *param_2;
  iVar23 = (int)(short)(ushort)*(byte *)(local_34 + 0x10);
  *(undefined4 *)(local_34 + 0xd4) = param_2[2];
  uVar26 = (uint)*(byte *)(local_34 + 0x11);
  iVar13 = iVar23 * 0x60;
  local_2c[0] = local_30;
  os_alloc_mem(0,local_2c,iVar13);
  if (local_2c[0] != 0) {
    if (iVar13 != 0) {
      __memzero(local_2c[0],iVar13);
    }
    *(int *)(iVar15 + 0x18) = local_2c[0];
    iVar13 = uVar26 * 0xa0;
    os_alloc_mem(0,&local_30,iVar13);
    if (local_30 != 0) {
      if (iVar13 != 0) {
        __memzero(local_30,iVar13);
      }
      *(int *)(iVar15 + 0x14) = local_30;
      if (uVar25 != 0) {
        uVar16 = 0;
        uVar17 = uVar16;
        do {
          uVar16 = uVar16 + 1;
          *(undefined4 *)(*(int *)(iVar15 + 0x18) + uVar17 + 0x34) = 0;
          iVar13 = *(int *)(iVar15 + 0x18) + uVar17;
          uVar17 = uVar17 + 0x60;
          *(undefined4 *)(iVar13 + 0x38) = 0;
        } while (uVar16 != uVar25);
      }
      if (uVar26 != 0) {
        uVar16 = 0;
        uVar17 = uVar16;
        do {
          uVar16 = uVar16 + 1;
          iVar13 = *(int *)(iVar15 + 0x14) + uVar17;
          uVar17 = uVar17 + 0xa0;
          *(undefined4 *)(iVar13 + 0x54) = 0;
        } while (uVar16 != uVar26);
      }
    }
  }
  iVar13 = *(int *)(iVar15 + 0xc4);
  if (uVar25 != 0) {
    iVar23 = iVar23 * 3;
  }
  iVar18 = 0;
  *(undefined4 *)(iVar15 + 0xc0) = 0;
  if (uVar25 != 0) {
    iVar24 = iVar13;
    do {
      iVar10 = *(int *)(iVar15 + 0x18);
      uVar21 = *(undefined4 *)(iVar24 + 4);
      iVar12 = iVar10 + iVar18 * 4;
      uVar20 = *(undefined4 *)(iVar24 + 0xc);
      uVar7 = *(undefined2 *)(iVar24 + 8);
      uVar2 = *(undefined1 *)(iVar24 + 0x10);
      *(undefined4 *)(iVar12 + 0x2c) = *(undefined4 *)(iVar13 + iVar18);
      *(undefined4 *)(iVar12 + 0x54) = uVar21;
      *(undefined4 *)(iVar10 + iVar18 * 4) = uVar20;
      iVar18 = iVar18 + 0x18;
      *(undefined2 *)(iVar12 + 0x5a) = uVar7;
      *(undefined1 *)(iVar12 + 0x59) = uVar2;
      iVar24 = iVar24 + 0x18;
    } while (iVar18 != iVar23 << 3);
    puVar19 = *(undefined4 **)(iVar15 + 200);
    if (uVar26 != 0) goto LAB_001d0a08;
    *(undefined4 *)(iVar15 + 0x1c) = 0;
    *(undefined4 *)(iVar15 + 0x20) = 0;
LAB_001d0b68:
    iVar13 = *(int *)(iVar15 + 0x18);
    uVar16 = 0;
    puVar11 = (undefined1 *)(iVar15 + 0x23);
    uVar17 = 0;
    do {
      puVar1 = (uint *)(iVar13 + 0x54);
      iVar13 = iVar13 + 0x60;
      uVar17 = uVar17 | *puVar1;
      *(uint *)(iVar15 + 0x1c) = uVar17;
      puVar11 = puVar11 + 1;
      *puVar11 = (char)uVar16;
      uVar16 = uVar16 + 1;
      *(uint *)(iVar15 + 0x20) = uVar16;
    } while (uVar16 < uVar25);
    *(undefined4 *)(iVar15 + 0x44) = 0;
    *(undefined4 *)(iVar15 + 0x48) = 0;
    if (uVar26 != 0) {
LAB_001d0bb0:
      piVar14 = *(int **)(iVar15 + 0x14);
      uVar25 = 0;
      puVar11 = (undefined1 *)(iVar15 + 0x4b);
      uVar17 = 0;
      piVar22 = piVar14;
      do {
        puVar1 = (uint *)(piVar22 + 0x19);
        piVar22 = piVar22 + 0x28;
        uVar17 = uVar17 | *puVar1;
        *(uint *)(iVar15 + 0x44) = uVar17;
        puVar11 = puVar11 + 1;
        *puVar11 = (char)uVar25;
        uVar25 = uVar25 + 1;
        *(uint *)(iVar15 + 0x48) = uVar25;
      } while (uVar25 < uVar26);
      uVar25 = 0;
      *(undefined4 *)(iVar15 + 0x6c) = 0;
      *(undefined4 *)(iVar15 + 0x70) = 0;
      piVar22 = piVar14;
      do {
        while (*piVar22 == 4) {
          iVar13 = *(int *)(iVar15 + 0x70);
          *(uint *)(iVar15 + 0x6c) = *(uint *)(iVar15 + 0x6c) | piVar22[0x19];
          *(char *)(iVar15 + iVar13 + 0x74) = (char)uVar25;
          uVar25 = uVar25 + 1;
          *(int *)(iVar15 + 0x70) = iVar13 + 1;
          piVar22 = piVar22 + 0x28;
          if (uVar26 <= uVar25) goto LAB_001d0c4c;
        }
        uVar25 = uVar25 + 1;
        piVar22 = piVar22 + 0x28;
      } while (uVar25 < uVar26);
LAB_001d0c4c:
      *(undefined4 *)(iVar15 + 0x94) = 0;
      uVar25 = 0;
      *(undefined4 *)(iVar15 + 0x98) = 0;
      do {
        while (*piVar14 == 5) {
          iVar13 = *(int *)(iVar15 + 0x98);
          *(uint *)(iVar15 + 0x94) = *(uint *)(iVar15 + 0x94) | piVar14[0x19];
          *(char *)(iVar15 + iVar13 + 0x9c) = (char)uVar25;
          uVar25 = uVar25 + 1;
          *(int *)(iVar15 + 0x98) = iVar13 + 1;
          piVar14 = piVar14 + 0x28;
          if (uVar26 <= uVar25) goto LAB_001d0cb0;
        }
        uVar25 = uVar25 + 1;
        piVar14 = piVar14 + 0x28;
      } while (uVar25 < uVar26);
      goto LAB_001d0cb0;
    }
  }
  else {
    puVar19 = *(undefined4 **)(iVar15 + 200);
    if (uVar26 != 0) {
LAB_001d0a08:
      iVar13 = 0;
      do {
        uVar30 = puVar19[3];
        uVar31 = puVar19[4];
        iVar23 = *(int *)(iVar15 + 0x14);
        uVar20 = puVar19[6];
        uVar21 = puVar19[7];
        iVar18 = iVar23 + iVar13;
        uVar28 = puVar19[9];
        uVar2 = *(undefined1 *)((int)puVar19 + 0x2d);
        uVar27 = *puVar19;
        uVar7 = *(undefined2 *)(puVar19 + 2);
        uVar3 = *(undefined1 *)(puVar19 + 5);
        uVar29 = puVar19[8];
        uVar4 = *(undefined1 *)(puVar19 + 0xb);
        uVar8 = *(undefined2 *)((int)puVar19 + 0x2a);
        uVar9 = *(undefined2 *)(puVar19 + 10);
        *(undefined4 *)(iVar18 + 100) = puVar19[1];
        *(undefined4 *)(iVar18 + 0x4c) = uVar27;
        *(undefined4 *)(iVar23 + iVar13) = uVar30;
        iVar13 = iVar13 + 0xa0;
        *(undefined2 *)(iVar18 + 0x14) = uVar7;
        *(undefined4 *)(iVar18 + 0x80) = uVar31;
        *(undefined1 *)(iVar18 + 0x6c) = uVar3;
        *(undefined4 *)(iVar18 + 0x70) = uVar20;
        *(undefined4 *)(iVar18 + 0x74) = uVar21;
        *(undefined4 *)(iVar18 + 0x78) = uVar29;
        *(undefined4 *)(iVar18 + 0x7c) = uVar28;
        *(undefined2 *)(iVar18 + 4) = uVar9;
        *(undefined2 *)(iVar18 + 0x6a) = uVar8;
        *(undefined1 *)(iVar18 + 0x1d) = uVar4;
        *(undefined1 *)(iVar18 + 0x38) = uVar2;
        puVar19 = puVar19 + 0xd;
      } while (iVar13 != uVar26 * 0xa0);
      iVar13 = 0;
      uVar17 = 0;
      do {
        while( true ) {
          iVar23 = *(int *)(iVar15 + 0x14) + iVar13;
          iVar18 = *(int *)(*(int *)(iVar15 + 0x14) + iVar13);
          if ((iVar18 != 4) && (iVar18 != 5)) break;
          uVar17 = uVar17 + 1;
          *(undefined1 *)(iVar23 + 0x1f) = 0;
          *(undefined1 *)(iVar23 + 0x68) = 0;
          iVar13 = iVar13 + 0xa0;
          *(undefined1 *)(iVar23 + 0x1e) = 1;
          if (uVar17 == uVar26) goto LAB_001d0b54;
        }
        if (-1 < DebugLevel) {
          printk("%s: ring_attr:%d, unknown ring_attr\n","pci_data_init");
        }
        uVar17 = uVar17 + 1;
        iVar13 = iVar13 + 0xa0;
      } while (uVar17 != uVar26);
LAB_001d0b54:
      *(undefined4 *)(iVar15 + 0x1c) = 0;
      *(undefined4 *)(iVar15 + 0x20) = 0;
      if (uVar25 != 0) goto LAB_001d0b68;
      *(undefined4 *)(iVar15 + 0x44) = 0;
      *(undefined4 *)(iVar15 + 0x48) = 0;
      goto LAB_001d0bb0;
    }
    *(undefined4 *)(iVar15 + 0x1c) = 0;
    *(undefined4 *)(iVar15 + 0x20) = 0;
    *(undefined4 *)(iVar15 + 0x44) = 0;
    *(undefined4 *)(iVar15 + 0x48) = 0;
  }
  *(undefined4 *)(iVar15 + 0x6c) = 0;
  *(undefined4 *)(iVar15 + 0x70) = 0;
  *(undefined4 *)(iVar15 + 0x94) = 0;
  *(undefined4 *)(iVar15 + 0x98) = 0;
LAB_001d0cb0:
  iVar13 = local_34;
  bVar5 = *(byte *)(local_34 + 0x10);
  uVar20 = *(undefined4 *)(local_34 + 0xcc);
  bVar6 = *(byte *)(local_34 + 0x11);
  if (bVar5 != 0) {
    iVar23 = 0;
    uVar25 = 0;
    do {
      piVar22 = (int *)(*(int *)(iVar13 + 0x18) + iVar23);
      iVar23 = iVar23 + 0x60;
      uVar26 = (uint)*(ushort *)((int)piVar22 + 0x5a);
      FUN_001ced00(uVar20,piVar22 + 0xf,uVar26 << 4);
      if (piVar22[0x10] == 0) goto LAB_001d0e18;
      if (2 < DebugLevel) {
        printk("TxRing[%d]: Attr:%d, total %d bytes allocated\n",uVar25,*piVar22,piVar22[0xf]);
      }
      uVar17 = uVar25 + 1;
      if (*piVar22 == 0) {
        iVar15 = *(int *)(iVar13 + 0x6c4) * uVar26;
        piVar22[0x12] = iVar15;
        RTMP_AllocateFirstTxBuffer(uVar20,uVar25,iVar15,0,piVar22 + 0x13,piVar22 + 0x14);
        if (piVar22[0x13] == 0) {
          if (DebugLevel < 0) goto LAB_001d0e28;
          printk("Failed to allocate a big buffer\n");
          goto LAB_001d0e18;
        }
      }
      iVar15 = uVar26 * 0x24;
      os_alloc_mem(0,piVar22 + 3,iVar15);
      if (iVar15 != 0 && piVar22[3] != 0) {
        __memzero(piVar22[3],iVar15);
      }
      uVar25 = uVar17;
    } while (uVar17 != bVar5);
  }
  if (bVar6 != 0) {
    iVar23 = 0;
    local_60 = 0;
    do {
      iVar24 = *(int *)(iVar13 + 0x14) + iVar23;
      iVar18 = *(int *)(*(int *)(iVar13 + 0x14) + iVar23);
      uVar25 = (uint)*(ushort *)(iVar24 + 0x14);
      FUN_001ced00(uVar20,iVar24 + 0x58,uVar25 << 4);
      iVar15 = *(int *)(iVar13 + 0x14) + iVar23;
      if (*(int *)(iVar15 + 0x5c) == 0) {
LAB_001d0e18:
        if (0 < DebugLevel) {
          printk("<-- %s, Status=%x\n","pci_alloc_tx_rx_ring_mem",3);
        }
        if (-1 < DebugLevel) {
          printk("Failed to allocate memory - TxRxRing\n");
        }
LAB_001d0e28:
        iVar13 = local_34;
        os_free_mem(*(undefined4 *)(local_34 + 0x18));
        os_free_mem(*(undefined4 *)(iVar13 + 0x14));
        hif_ctrl_exit(local_34);
        return 3;
      }
      if (iVar18 == 5) {
        *(undefined2 *)(iVar15 + 0x20) = 0;
        *(short *)(iVar15 + 0x24) = (short)(uVar25 + 1);
        *(undefined2 *)(iVar15 + 0x22) = 0;
        os_alloc_mem(0,iVar15 + 0x28,(uVar25 + 1 & 0xffff) * 0xc);
        if (*(int *)(iVar15 + 0x28) != 0) {
          uVar26 = (uint)*(ushort *)(iVar15 + 0x24);
          if (uVar26 * 0xc != 0) {
            __memzero();
            uVar26 = (uint)*(ushort *)(iVar15 + 0x24);
          }
          if (uVar26 != 0) {
            iVar18 = 0;
            uVar26 = 0;
            do {
              iVar10 = *(int *)(iVar15 + 0x28);
              uVar26 = uVar26 + 1;
              *(undefined4 *)(iVar10 + iVar18) = 0x6a4;
              os_alloc_mem(0,iVar10 + iVar18 + 4);
              if ((*(int *)(iVar10 + iVar18 + 4) != 0) && (*(int *)(iVar10 + iVar18) != 0)) {
                __memzero();
              }
              iVar18 = iVar18 + 0xc;
            } while (uVar26 < *(ushort *)(iVar15 + 0x24));
          }
        }
        *(undefined2 *)(iVar15 + 0x40) = 0;
        *(undefined2 *)(iVar15 + 0x44) = 1;
        *(undefined2 *)(iVar15 + 0x42) = 0;
        os_alloc_mem(0,iVar15 + 0x48,0xc);
        if (*(int *)(iVar15 + 0x48) != 0) {
          uVar26 = (uint)*(ushort *)(iVar15 + 0x44);
          if (uVar26 * 0xc != 0) {
            __memzero();
            uVar26 = (uint)*(ushort *)(iVar15 + 0x44);
          }
          if (uVar26 != 0) {
            iVar18 = 0;
            uVar26 = 0;
            do {
              iVar10 = *(int *)(iVar15 + 0x48);
              uVar26 = uVar26 + 1;
              *(undefined4 *)(iVar10 + iVar18) = 0x10000;
              os_alloc_mem(0,iVar10 + iVar18 + 4);
              if ((*(int *)(iVar10 + iVar18 + 4) != 0) && (*(int *)(iVar10 + iVar18) != 0)) {
                __memzero();
              }
              iVar18 = iVar18 + 0xc;
            } while (uVar26 < *(ushort *)(iVar15 + 0x44));
          }
        }
      }
      if (0 < DebugLevel) {
        printk("Rx[%d] Ring: total %d bytes allocated\n",local_60,
               *(undefined4 *)(*(int *)(iVar13 + 0x14) + iVar23 + 0x58));
      }
      iVar15 = uVar25 * 0x24;
      os_alloc_mem(0,iVar24 + 0x18,iVar15);
      if (iVar15 != 0 && *(int *)(iVar24 + 0x18) != 0) {
        __memzero(*(int *)(iVar24 + 0x18),iVar15);
      }
      iVar23 = iVar23 + 0xa0;
      local_60 = local_60 + 1;
    } while (local_60 != bVar6);
  }
  if (0 < DebugLevel) {
    printk("<-- %s, Status=%x\n","pci_alloc_tx_rx_ring_mem",0);
  }
  *param_1 = local_34;
  return 0;
}

