// module: mt7915.ko
// function: MlmeUpdateTxRatesWdev @ 0x12b270
// size: 2612 bytes
//

void MlmeUpdateTxRatesWdev(int param_1,uint param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  byte *pbVar7;
  byte *pbVar8;
  undefined1 *puVar10;
  char cVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  undefined1 auStack_2a [6];
  byte *pbVar9;
  
  if (param_3 == 0) {
    return;
  }
  uVar15 = 0;
  UpdateBasicRateBitmap(param_1,param_3);
  pbVar7 = (byte *)(param_3 + 0xaf7);
  iVar16 = 0;
  uVar4 = 4;
  do {
    pbVar7 = pbVar7 + 1;
    switch(*pbVar7 & 0x7f) {
    case 2:
      iVar16 = iVar16 + 1;
      uVar4 = 0;
      goto LAB_0012b484;
    case 4:
      iVar16 = iVar16 + 1;
      uVar4 = 1;
      break;
    case 0xb:
      iVar16 = iVar16 + 1;
      uVar4 = 2;
      break;
    case 0xc:
      iVar16 = iVar16 + 1;
      uVar4 = 4;
      break;
    case 0x12:
      iVar16 = iVar16 + 1;
      uVar4 = 5;
      break;
    case 0x16:
      iVar16 = iVar16 + 1;
      uVar4 = 3;
      break;
    case 0x18:
      iVar16 = iVar16 + 1;
      uVar4 = 6;
      break;
    case 0x24:
      iVar16 = iVar16 + 1;
      uVar4 = 7;
      break;
    case 0x30:
      iVar16 = iVar16 + 1;
      uVar4 = 8;
      break;
    case 0x48:
      iVar16 = iVar16 + 1;
      uVar4 = 9;
      break;
    case 0x60:
      iVar16 = iVar16 + 1;
      uVar4 = 10;
      break;
    case 0x6c:
      iVar16 = iVar16 + 1;
      uVar4 = 0xb;
    }
    if (uVar15 < uVar4) {
      uVar15 = uVar4;
    }
LAB_0012b484:
  } while (pbVar7 != (byte *)(param_3 + 0xb03));
  if (*(char *)(param_1 + 0x286285) == '\0') {
    iVar3 = GetStaCfgByWdev(param_1,param_3);
    if (((iVar3 != 0) && (*(char *)(iVar3 + 0x4060) == '\0')) &&
       (*(short *)(param_3 + 0x18) == 2 && 3 < uVar15)) {
      uVar15 = 3;
    }
  }
  else {
    iVar3 = 0;
  }
  uVar4 = *(byte *)(param_3 + 0x8ae) & 0x7f;
  *(char *)(param_3 + 0xb04) = (char)uVar15;
  *(undefined2 *)(param_3 + 0x8b6) = 0;
  *(undefined2 *)(param_3 + 0x8b4) = 0;
  *(undefined2 *)(param_3 + 0x8b2) = 0;
  *(bool *)(param_3 + 0x8b0) = 1 < iVar16;
  *(bool *)(param_3 + 0x8b0) = uVar4 == 0x21 || uVar4 == 0x21 && 1 < iVar16;
  if (((iVar3 == 0) ||
      (((*(uint *)(param_1 + 0x795124) & 2) == 0 && ((*(uint *)(iVar3 + 0x212464) & 1) == 0)))) ||
     ((*(int *)(param_3 + 0x14) - 2U & 0xfffffffd) != 0)) {
    pbVar7 = (byte *)(param_3 + 0xade);
  }
  else {
    pbVar7 = (byte *)(iVar3 + 0x40c6);
  }
  if (*pbVar7 == 0) {
    uVar17 = 0xb;
    uVar13 = 0;
    uVar14 = 0;
  }
  else {
    uVar13 = 0;
    uVar14 = 0;
    pbVar9 = pbVar7 + 1;
    uVar5 = 0xb;
    do {
      pbVar8 = pbVar9 + 1;
      bVar1 = *pbVar9;
      switch(bVar1 & 0x7f) {
      case 2:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 1;
        }
      default:
        uVar17 = 0;
        goto LAB_0012b7c4;
      case 4:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 2;
        }
        uVar17 = 1;
        break;
      case 0xb:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 4;
        }
        uVar17 = 2;
        break;
      case 0xc:
        uVar13 = uVar13 | 0x10;
        uVar17 = 4;
        break;
      case 0x12:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 0x20;
        }
        uVar17 = 5;
        break;
      case 0x16:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 8;
        }
        uVar17 = 3;
        break;
      case 0x18:
        uVar13 = uVar13 | 0x40;
        uVar17 = 6;
        break;
      case 0x24:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 0x80;
        }
        uVar17 = 7;
        break;
      case 0x30:
        uVar13 = uVar13 | 0x100;
        uVar17 = 8;
        break;
      case 0x48:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 0x200;
        }
        uVar17 = 9;
        break;
      case 0x60:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 0x400;
          uVar17 = 10;
          break;
        }
        uVar17 = 10;
        if (9 < uVar14) goto LAB_0012b9b8;
        goto LAB_0012b7b4;
      case 0x6c:
        if ((bVar1 & 0x80) == 0) {
          uVar17 = 0xb;
        }
        else {
          uVar13 = uVar13 | 0x800;
          uVar17 = 0xb;
        }
      }
      if (uVar14 < uVar17) {
LAB_0012b7b4:
        uVar14 = uVar17;
        if (uVar5 <= uVar17) {
          uVar17 = uVar5;
        }
      }
      else {
LAB_0012b9b8:
        if (uVar5 <= uVar17) {
          uVar17 = uVar5;
        }
      }
LAB_0012b7c4:
      pbVar9 = pbVar8;
      uVar5 = uVar17;
    } while (pbVar8 != pbVar7 + 1 + *pbVar7);
  }
  if (pbVar7[0xd] != 0) {
    uVar5 = uVar17;
    pbVar9 = pbVar7 + 0xe;
    do {
      pbVar8 = pbVar9 + 1;
      bVar1 = *pbVar9;
      switch(bVar1 & 0x7f) {
      case 2:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 1;
        }
      default:
        uVar17 = 0;
        goto LAB_0012baa0;
      case 4:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 2;
        }
        uVar17 = 1;
        break;
      case 0xb:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 4;
        }
        uVar17 = 2;
        break;
      case 0xc:
        uVar13 = uVar13 | 0x10;
        uVar17 = 4;
        break;
      case 0x12:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 0x20;
        }
        uVar17 = 5;
        break;
      case 0x16:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 8;
        }
        uVar17 = 3;
        break;
      case 0x18:
        uVar13 = uVar13 | 0x40;
        uVar17 = 6;
        break;
      case 0x24:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 0x80;
        }
        uVar17 = 7;
        break;
      case 0x30:
        uVar13 = uVar13 | 0x100;
        uVar17 = 8;
        break;
      case 0x48:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 0x200;
        }
        uVar17 = 9;
        break;
      case 0x60:
        if ((bVar1 & 0x80) != 0) {
          uVar13 = uVar13 | 0x400;
          uVar17 = 10;
          break;
        }
        uVar17 = 10;
        if (9 < uVar14) goto LAB_0012bd18;
        goto LAB_0012ba90;
      case 0x6c:
        if ((bVar1 & 0x80) == 0) {
          uVar17 = 0xb;
        }
        else {
          uVar13 = uVar13 | 0x800;
          uVar17 = 0xb;
        }
      }
      if (uVar14 < uVar17) {
LAB_0012ba90:
        uVar14 = uVar17;
        if (uVar5 <= uVar17) {
          uVar17 = uVar5;
        }
      }
      else {
LAB_0012bd18:
        if (uVar5 <= uVar17) {
          uVar17 = uVar5;
        }
      }
LAB_0012baa0:
      uVar5 = uVar17;
      pbVar9 = pbVar8;
    } while (pbVar8 != pbVar7 + 0xe + pbVar7[0xd]);
  }
  uVar5 = 0;
  puVar10 = (undefined1 *)(param_1 + 0x794c8e);
  uVar12 = 0;
  do {
    if ((uVar13 & 1 << (uVar12 & 0xff)) != 0) {
      uVar5 = uVar12 & 0xff;
    }
    uVar12 = uVar12 + 1;
    puVar10 = puVar10 + 1;
    *puVar10 = (char)uVar5;
  } while (uVar12 != 0xc);
  if (2 < DebugLevel) {
    printk("%s():[MaxSupport = %d] = MaxDesire %d Mbps\n","MlmeUpdateTxRatesWdev",
           RateIdToMbps[uVar14],RateIdToMbps[uVar15]);
  }
  if (uVar14 < uVar15) {
    *(char *)(param_3 + 0xb05) = (char)uVar14;
    uVar5 = uVar14;
  }
  else {
    *(char *)(param_3 + 0xb05) = (char)uVar15;
    uVar5 = uVar15;
  }
  *(char *)(param_3 + 0xb07) = (char)uVar17;
  uVar2 = (undefined1)uVar5;
  uVar12 = param_2;
  if (*(char *)(param_3 + 0x8b0) == '\0') {
    *(undefined1 *)(param_3 + 0xb08) = uVar2;
    uVar15 = uVar17;
    if (iVar16 < 5) {
      if (uVar4 < 4) {
        uVar15 = uVar4;
      }
    }
    else if (uVar4 < 8) {
      uVar15 = (uint)(byte)RxwiMCSToOfdmRate[uVar4];
    }
    if (param_2 != 0) {
      uVar12 = 1;
    }
    if (*(char *)(param_1 + 0x286285) == '\0') {
      uVar4 = uVar12 & 1;
    }
    else {
      uVar4 = 0;
    }
    if (uVar4 != 0) {
      iVar16 = GetAssociatedAPByWdev(param_1,param_3);
      uVar12 = uVar4;
      if (iVar16 == 0) {
        uVar5 = (uint)*(byte *)(param_3 + 0xb08);
      }
      else {
        *(byte *)(iVar16 + 0xbd) =
             *(byte *)(iVar16 + 0xbd) & 0xfb |
             (byte)((((uint)*(byte *)(param_3 + 0x8b3) << 0x1d) >> 0x1f) << 2);
        *(byte *)(iVar16 + 0xbd) =
             *(byte *)(iVar16 + 0xbd) & 0xfd |
             (byte)((((uint)*(byte *)(param_3 + 0x8b3) << 0x1e) >> 0x1f) << 1);
        *(byte *)(iVar16 + 0xbc) =
             *(byte *)(iVar16 + 0xbc) & 0xc0 | *(byte *)(param_3 + 0x8b2) & 0x3f;
        *(byte *)(iVar16 + 0xbd) =
             *(byte *)(iVar16 + 0xbd) & 0x1f | *(byte *)(param_3 + 0x8b3) & 0xe0;
        uVar5 = (uint)*(byte *)(param_3 + 0xb08);
      }
    }
  }
  else {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      sVar6 = (short)(char)(&DAT_00580d24)[param_1] -
              (short)"rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x12];
    }
    else {
      sVar6 = 0;
    }
    if (param_2 == 1) {
      *(undefined1 *)(param_3 + 0xb08) = 8;
    }
    else {
      *(undefined1 *)(param_3 + 0xb08) = uVar2;
    }
    if (sVar6 < -0x4b) {
      uVar4 = 3;
      *(undefined1 *)(param_3 + 0xb08) = 3;
    }
    else if (sVar6 < -0x46) {
      uVar4 = 8;
      *(undefined1 *)(param_3 + 0xb08) = 8;
    }
    else {
      uVar4 = (uint)*(byte *)(param_3 + 0xb08);
    }
    if (uVar5 < uVar4) {
      *(undefined1 *)(param_3 + 0xb08) = uVar2;
      uVar4 = uVar5;
    }
    *(undefined1 *)(param_3 + 0xb06) = 0;
    uVar5 = uVar4;
    if (param_2 != 0) {
      uVar12 = 1;
    }
  }
  if (uVar5 < 4) {
    *(byte *)(param_3 + 0x8b5) = *(byte *)(param_3 + 0x8b5) & 0x1f;
    cVar11 = *(char *)(param_1 + 0x286285);
    if (cVar11 == '\0') {
      *(byte *)(param_3 + 0x8b4) =
           *(byte *)(param_3 + 0x8b4) & 0xc0 | *(byte *)(param_1 + 0x794cd0) & 0x3f;
      *(byte *)(param_3 + 0x8b6) =
           *(byte *)(param_3 + 0x8b6) & 0xc0 | *(byte *)(param_1 + 0x794cd3) & 0x3f;
      cVar11 = *(char *)(param_1 + 0x286285);
    }
    if (cVar11 == '\x01') {
      *(byte *)(param_3 + 0x8b4) = *(byte *)(param_3 + 0x8b4) & 0xc0 | (byte)uVar15 & 0x3f;
    }
  }
  else {
    *(byte *)(param_3 + 0x8b5) = *(byte *)(param_3 + 0x8b5) & 0x1f | 0x20;
    cVar11 = *(char *)(param_1 + 0x286285);
    if (cVar11 == '\0') {
      *(byte *)(param_3 + 0x8b4) =
           *(byte *)(param_3 + 0x8b4) & 0xc0 |
           OfdmRateToRxwiMCS[*(byte *)(param_1 + 0x794cd0)] & 0x3f;
      bVar1 = *(byte *)(param_1 + 0x794cd3);
      if (bVar1 - 4 < 8) {
        *(byte *)(param_3 + 0x8b6) =
             *(byte *)(param_3 + 0x8b6) & 0xc0 | OfdmRateToRxwiMCS[bVar1] & 0x3f;
      }
      else {
        *(byte *)(param_3 + 0x8b6) = *(byte *)(param_3 + 0x8b6) & 0xc0 | bVar1 & 0x3f;
      }
      cVar11 = *(char *)(param_1 + 0x286285);
    }
    if (cVar11 == '\x01') {
      *(byte *)(param_3 + 0x8b4) =
           *(byte *)(param_3 + 0x8b4) & 0xc0 | OfdmRateToRxwiMCS[uVar15] & 0x3f;
    }
  }
  *(undefined2 *)(param_3 + 0x8b2) = *(undefined2 *)(param_3 + 0x8b4);
  if ((param_2 == 0) || (*(char *)(param_1 + 0x286285) != '\0')) {
    if (((*(ushort *)(param_3 + 0x18) & 2) == 0) || (0xe < *(byte *)(param_3 + 0x1a))) {
      *(undefined1 *)(param_1 + 0x794cd5) = 4;
      *(undefined1 *)(param_1 + 0x794cd4) = 4;
      *(byte *)(param_3 + 0xb0b) = *(byte *)(param_3 + 0xb0b) & 0x1f | 0x20;
      *(byte *)(param_3 + 0xb0a) =
           *(byte *)(param_3 + 0xb0a) & 0xc0 |
           OfdmRateToRxwiMCS[*(byte *)(param_1 + 0x794cd5)] & 0x3f;
    }
    else {
      *(undefined1 *)(param_1 + 0x794cd5) = 0;
      *(byte *)(param_3 + 0xb0b) = *(byte *)(param_3 + 0xb0b) & 0x1f;
      *(byte *)(param_3 + 0xb0a) = *(byte *)(param_3 + 0xb0a) & 0xc0;
      *(undefined1 *)(param_1 + 0x794cd4) = 3;
    }
    *(undefined2 *)(param_1 + 0xa1ddc) = *(undefined2 *)(param_3 + 0xb0a);
    if ((*(byte *)(param_3 + 0xb0b) & 0xe0) == 0x20) {
      *(byte *)(param_1 + 0xa1ddc) =
           *(byte *)(param_1 + 0xa1ddc) & 0xc0 | OfdmRateToRxwiMCS[8] & 0x3f;
    }
    else {
      *(byte *)(param_1 + 0xa1ddc) = *(byte *)(param_1 + 0xa1ddc) & 0xc0;
    }
    *(undefined1 *)(param_1 + 0x794cd6) = *(undefined1 *)(param_1 + 0x794cd5);
    __memzero(auStack_2a,2);
    iVar16 = memcmp((void *)(param_3 + 0xb0c),auStack_2a,2);
    if (iVar16 == 0) {
      memmove((void *)(param_3 + 0xb0c),(void *)(param_1 + 0xa1ddc),2);
    }
  }
  else {
    iVar16 = GetAssociatedAPByWdev(param_1,param_3);
    if (iVar16 != 0) {
      *(undefined2 *)(iVar16 + 0xbc) = *(undefined2 *)(param_3 + 0x8b2);
      *(undefined2 *)(iVar16 + 0xbe) = *(undefined2 *)(param_3 + 0x8b4);
      *(undefined2 *)(iVar16 + 0xc0) = *(undefined2 *)(param_3 + 0x8b6);
    }
  }
  if (2 < DebugLevel) {
    uVar4 = (uint)(byte)RateIdToMbps[*(byte *)(param_3 + 0xb07)];
    uVar17 = (uint)*(byte *)(param_3 + 0x8b0);
    printk(" %s(): (MaxDesire=%d, MaxSupport=%d, MaxTxRate=%d, MinRate=%d, Rate Switching =%d)\n",
           "MlmeUpdateTxRatesWdev",RateIdToMbps[uVar15],RateIdToMbps[uVar14],
           RateIdToMbps[*(byte *)(param_3 + 0xb05)],uVar4,uVar17);
    if (2 < DebugLevel) {
      printk(" %s(): (TxRate=%d, RtsRate=%d, BasicRateBitmap=0x%04lx)\n","MlmeUpdateTxRatesWdev",
             RateIdToMbps[*(byte *)(param_3 + 0xb08)],RateIdToMbps[*(byte *)(param_1 + 0x794cd4)],
             uVar13,uVar4,uVar17);
    }
  }
  if (*(char *)(param_1 + 0x286285) == '\0') {
    uVar12 = uVar12 & 1;
  }
  else {
    uVar12 = 0;
  }
  if (((uVar12 != 0) && (iVar16 = GetAssociatedAPByWdev(param_1,param_3), iVar16 != 0)) &&
     (2 < DebugLevel)) {
    printk("%s(): (MlmeTransmit=0x%x, MinHTPhyMode=%x, MaxHTPhyMode=0x%x, HTPhyMode=0x%x)\n",
           "MlmeUpdateTxRatesWdev",*(undefined2 *)(param_3 + 0xb0a),*(undefined2 *)(iVar16 + 0xc0),
           *(undefined2 *)(iVar16 + 0xbe),*(undefined2 *)(iVar16 + 0xbc));
  }
  return;
}

