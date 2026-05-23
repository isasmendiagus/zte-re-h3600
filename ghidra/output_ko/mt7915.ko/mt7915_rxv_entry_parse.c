// module: mt7915.ko
// function: mt7915_rxv_entry_parse @ 0x178bf8
// size: 2308 bytes
//

undefined4 mt7915_rxv_entry_parse(int param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char *pcVar5;
  uint uVar6;
  byte *pbVar7;
  uint *puVar8;
  uint *puVar9;
  int iVar10;
  int *piVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  char *pcVar15;
  int iVar16;
  uint *puVar17;
  undefined4 *puVar18;
  int iVar19;
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar14 = (uint)(*param_2 << 9) >> 0x19;
  iVar2 = (param_2[1] << 7) >> 0x1f;
  if (DebugLevel < 3) {
    if (0x10 < uVar14) {
      return 1;
    }
  }
  else {
    printk("%s(): sta_cnt: %d, band_idx: %d\n","mt7915_rxv_entry_parse",uVar14);
    if (0x10 < uVar14) {
      if (DebugLevel < 3) {
        return 1;
      }
      printk("%s(): sta count is invalid(%d).\n","mt7915_rxv_entry_parse",uVar14);
      return 1;
    }
  }
  uVar6 = (uint)*(byte *)(iVar3 + 0x214);
  if (uVar6 == 0) {
    iVar16 = 0;
  }
  else {
    uVar12 = 0;
    do {
      if (3 < DebugLevel) {
        printk("HEADER(%d): 0x%x\n",uVar12,param_2[uVar12]);
        uVar6 = (uint)*(byte *)(iVar3 + 0x214);
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < uVar6);
    iVar16 = uVar6 << 2;
  }
  uVar6 = (uint)*(byte *)(iVar3 + 0x215);
  iVar10 = 0;
  if (uVar6 != 0) {
    uVar12 = 0;
    do {
      if (3 < DebugLevel) {
        printk("CMN1(%d): 0x%x\n",uVar12,*(undefined4 *)((int)param_2 + uVar12 * 4 + iVar16));
        uVar6 = (uint)*(byte *)(iVar3 + 0x215);
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < uVar6);
    iVar10 = uVar6 << 2;
  }
  iVar16 = (int)param_2 + iVar10 + iVar16;
  if (uVar14 != 0) {
    uVar6 = (uint)*(byte *)(iVar3 + 0x217);
    uVar12 = 0;
    do {
      if (uVar14 * uVar6 != 0) {
        uVar13 = 0;
        do {
          if (3 < DebugLevel) {
            printk("user_idx: %d, USR1(%d): 0x%x\n",uVar12,uVar13,
                   *(undefined4 *)(iVar16 + uVar13 * 4));
            uVar6 = (uint)*(byte *)(iVar3 + 0x217);
          }
          uVar13 = uVar13 + 1;
        } while (uVar13 <= uVar14 * uVar6 && uVar14 * uVar6 - uVar13 != 0);
      }
      uVar12 = uVar12 + 1;
      iVar16 = iVar16 + uVar6 * 4;
    } while ((uVar12 & 0xff) < uVar14);
    uVar6 = (uint)*(byte *)(iVar3 + 0x218);
    uVar12 = 0;
    do {
      if (uVar14 * uVar6 != 0) {
        uVar13 = 0;
        do {
          if (3 < DebugLevel) {
            printk("user_idx: %d, USR2(%d): 0x%x\n",uVar12,uVar13,
                   *(undefined4 *)(iVar16 + uVar13 * 4));
            uVar6 = (uint)*(byte *)(iVar3 + 0x218);
          }
          uVar13 = uVar13 + 1;
        } while (uVar13 <= uVar14 * uVar6 && uVar14 * uVar6 - uVar13 != 0);
      }
      uVar12 = uVar12 + 1;
      iVar16 = iVar16 + uVar6 * 4;
    } while ((uVar12 & 0xff) < uVar14);
  }
  uVar6 = (uint)*(byte *)(iVar3 + 0x216);
  if (uVar6 != 0) {
    uVar12 = 0;
    do {
      if (3 < DebugLevel) {
        printk("CMN2(%d): 0x%x\n",uVar12,*(undefined4 *)(iVar16 + uVar12 * 4));
        uVar6 = (uint)*(byte *)(iVar3 + 0x216);
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < uVar6);
  }
  uVar6 = (uint)*(byte *)(iVar3 + 0x214);
  iVar16 = iVar2 * -0x168;
  iVar10 = param_1 + iVar16;
  *(byte *)(iVar10 + 0xa7c054) = (byte)param_2[uVar6] >> 4;
  *(byte *)(iVar10 + 0xa7c055) = (byte)((uint)(param_2[uVar6 + 2] << 4) >> 0x1a);
  *(uint *)(iVar10 + 0xa7bfd4) = (uint)*(byte *)(param_2 + uVar6 + 6);
  *(uint *)(iVar10 + 0xa7bfd8) = (uint)*(byte *)((int)param_2 + uVar6 * 4 + 0x19);
  iVar19 = 0;
  *(uint *)(iVar10 + 0xa7bfdc) = (uint)*(byte *)((int)param_2 + uVar6 * 4 + 0x1a);
  *(uint *)(iVar10 + 0xa7bfe0) = (uint)*(byte *)((int)param_2 + uVar6 * 4 + 0x1b);
  piVar11 = (int *)(param_1 + iVar16 + 0xa7bfd0);
  do {
    piVar4 = piVar11 + 1;
    iVar19 = iVar19 + 1;
    if (*piVar4 == 0xff) {
      *piVar4 = 0;
      piVar11[-0x13] = -0x7f;
    }
    else {
      piVar11[-0x13] = (*piVar4 + -0xdc) / 2;
    }
    piVar11 = piVar4;
  } while (iVar19 != 4);
  iVar19 = param_1 + iVar2 * -0x168;
  *(uint *)(iVar19 + 0xa7bfe4) = (uint)*(byte *)(param_2 + uVar6 + 7);
  *(uint *)(iVar19 + 0xa7bfe8) = (uint)*(byte *)((int)param_2 + uVar6 * 4 + 0x1d);
  piVar11 = (int *)(param_1 + iVar16 + 0xa7bfe0);
  *(uint *)(iVar19 + 0xa7bfec) = (uint)*(byte *)((int)param_2 + uVar6 * 4 + 0x1e);
  iVar10 = 0;
  *(uint *)(iVar19 + 0xa7bff0) = (uint)*(byte *)((int)param_2 + uVar6 * 4 + 0x1f);
  do {
    piVar11 = piVar11 + 1;
    iVar10 = iVar10 + 1;
    if (0x7f < *piVar11) {
      *piVar11 = *piVar11 + -0x100;
    }
  } while (iVar10 != 4);
  iVar10 = param_1 + iVar2 * -0x168;
  *(uint *)(iVar10 + 0xa7bff4) = (uint)(param_2[uVar6 + 8] << 0x13) >> 0x18;
  *(uint *)(iVar10 + 0xa7bff8) = (uint)(param_2[uVar6 + 8] << 10) >> 0x18;
  *(uint *)(iVar10 + 0xa7bffc) = (uint)(param_2[uVar6 + 8] << 1) >> 0x18;
  piVar11 = (int *)(param_1 + iVar16 + 0xa7bff0);
  iVar19 = 0;
  *(uint *)(iVar10 + 0xa7c000) = (uint)*(byte *)(param_2 + uVar6 + 9);
  do {
    piVar11 = piVar11 + 1;
    iVar19 = iVar19 + 1;
    if (0x7f < *piVar11) {
      *piVar11 = *piVar11 + -0x100;
    }
    iVar10 = DebugLevel;
  } while (iVar19 != 4);
  puVar17 = (uint *)(param_2 + uVar6 + *(byte *)(iVar3 + 0x215));
  if (uVar14 == 0) {
    iVar3 = param_1 + iVar2 * -0x168;
    *(int *)(iVar3 + 0xa7bf40) = *(int *)(iVar3 + 0xa7bf40) + 1;
  }
  else {
    uVar6 = uVar14 - 1 & 0xff;
    pbVar7 = (byte *)(param_1 + iVar16 + 0xa7c055);
    do {
      pbVar7 = pbVar7 + 1;
      *pbVar7 = (byte)(puVar17[1] >> 0x1f);
      puVar17 = puVar17 + *(byte *)(iVar3 + 0x217);
    } while (pbVar7 != (byte *)(param_1 + iVar16 + 0xa7c056 + uVar6));
    pbVar7 = (byte *)(param_1 + iVar16 + 0xa7c003);
    puVar8 = (uint *)(param_1 + iVar16 + 0xa7bf40);
    do {
      puVar9 = puVar8 + 1;
      *puVar9 = *puVar17 >> 0x13 | (puVar17[1] & 0x7f) << 0xd;
      puVar8[0x15] = ((*puVar17 << 0xd) >> 0x1a) - 0x10;
      uVar12 = puVar17[1];
      pbVar7 = pbVar7 + 1;
      *pbVar7 = (byte)((uVar12 << 0x12) >> 0x1f);
      if ((int)(uVar12 << 0x12) < 0) {
        puVar8[0x35] = puVar8[0x35] + 1;
      }
      puVar17 = puVar17 + *(byte *)(iVar3 + 0x218);
      puVar8 = puVar9;
    } while (puVar9 != (uint *)(param_1 +
                               (int)("CmdETxBfPfmuProfileDataWrite20MAll" +
                                    uVar6 + iVar2 * -0x5a + 0x11) * 4));
    pcVar15 = (char *)(param_1 + iVar16 + 0xa7c004);
    iVar3 = param_1 + iVar2 * -0x168;
    piVar11 = (int *)(param_1 + iVar16 + 0xa7c068);
    uVar6 = 0;
    pcVar5 = pcVar15;
    do {
      cVar1 = *(char *)(iVar3 + 0xa7c054);
      if (cVar1 == '\x04') {
        if ((*pcVar5 == '\0') &&
           (cVar1 = *(char *)(iVar3 + 0xa7c055), cVar1 != '?' && cVar1 != '\0')) {
LAB_001790fc:
          *piVar11 = *piVar11 + 1;
          if (uVar6 == 0) {
            *(int *)(param_1 + 0xa789d8) = *(int *)(param_1 + 0xa789d8) + 1;
          }
        }
      }
      else if ((cVar1 == '\v') && (*pcVar5 == '\0')) goto LAB_001790fc;
      iVar10 = DebugLevel;
      uVar6 = uVar6 + 1;
      piVar11 = piVar11 + 1;
      pcVar5 = pcVar5 + 1;
    } while ((uVar6 & 0xff) < uVar14);
    puVar18 = (undefined4 *)(param_1 + iVar16 + 0xa7bf94);
    iVar3 = param_1 + iVar2 * -0x168;
    uVar6 = 0;
    *(int *)(iVar3 + 0xa7bf40) = *(int *)(iVar3 + 0xa7bf40) + 1;
    do {
      if ((((2 < iVar10) &&
           (printk("\t user_idx: %d, FreqOffsetFromRx = %d \n",uVar6,puVar18[-0x14]),
           iVar10 = DebugLevel, 2 < DebugLevel)) &&
          (printk("\t user_idx: %d, fcs_error: %d, fcs error cnt: %d \n",uVar6,*pcVar15,
                  puVar18[0x20]), iVar10 = DebugLevel, 2 < DebugLevel)) &&
         (printk("\t user_idx: %d, rx_vld_ind: %d, fcs_error: %d, rx mu ok cnt: %d \n",uVar6,
                 pcVar15[0x52],*pcVar15,puVar18[0x35]), iVar10 = DebugLevel, 2 < DebugLevel)) {
        printk("\t user_idx: %d,  SNR: %d \n",uVar6,*puVar18);
        iVar10 = DebugLevel;
      }
      uVar6 = uVar6 + 1;
      puVar18 = puVar18 + 1;
      pcVar15 = pcVar15 + 1;
    } while ((uVar6 & 0xff) < uVar14);
  }
  if (2 < iVar10) {
    param_1 = param_1 + iVar2 * -0x168;
    printk("\t pfd(txmode): %d, vht_gid: %d \n",*(undefined1 *)(param_1 + 0xa7c054),
           *(undefined1 *)(param_1 + 0xa7c055));
    if (((2 < DebugLevel) &&
        (printk("\t RCPI: (%d,%d,%d,%d) \n",*(undefined4 *)(param_1 + 0xa7bfd4),
                *(undefined4 *)(param_1 + 0xa7bfd8),*(undefined4 *)(param_1 + 0xa7bfdc),
                *(undefined4 *)(param_1 + 0xa7bfe0)), 2 < DebugLevel)) &&
       ((printk("\t RSSI: (%d,%d,%d,%d) \n",*(undefined4 *)(param_1 + 0xa7bf84),
                *(undefined4 *)(param_1 + 0xa7bf88),*(undefined4 *)(param_1 + 0xa7bf8c),
                *(undefined4 *)(param_1 + 0xa7bf90)), 2 < DebugLevel &&
        (printk("\t FAGC_RSSI_IB: (%d,%d,%d,%d) \n",*(undefined4 *)(param_1 + 0xa7bfe4),
                *(undefined4 *)(param_1 + 0xa7bfe8),*(undefined4 *)(param_1 + 0xa7bfec),
                *(undefined4 *)(param_1 + 0xa7bff0)), 2 < DebugLevel)))) {
      printk("\t FAGC_RSSI_WB: (%d,%d,%d,%d) \n",*(undefined4 *)(param_1 + 0xa7bff4),
             *(undefined4 *)(param_1 + 0xa7bff8),*(undefined4 *)(param_1 + 0xa7bffc),
             *(undefined4 *)(param_1 + 0xa7c000));
    }
  }
  return 0;
}

