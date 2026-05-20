// module: mt7915.ko
// function: CCI_ACI_scenario_maintain @ 0xc8464
// size: 948 bytes
//

void CCI_ACI_scenario_maintain(int param_1)

{
  short sVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  int *unaff_r5;
  uint uVar7;
  uint uVar8;
  short *psVar9;
  int *piVar10;
  int *piVar11;
  int *piVar12;
  int iVar13;
  int iVar14;
  bool bVar15;
  bool bVar16;
  int *local_4c;
  int *local_48;
  uint local_40;
  byte local_30 [12];
  
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  local_30[3] = 0;
  local_30[4] = 0;
  local_30[5] = 0;
  local_30[6] = 0;
  local_30[7] = 0;
  local_40 = HcGetAmountOfBand();
  if (local_40 < 3) {
    if (local_40 == 0) {
      return;
    }
  }
  else {
    if (-1 < DebugLevel) {
      printk("It should not happen!!!!!");
    }
    local_40 = 2;
  }
  uVar8 = 0;
  piVar12 = (int *)(param_1 + 0xa7c314);
  piVar11 = (int *)(param_1 + 0xa7c31c);
  local_4c = (int *)(param_1 + 0xa7c324);
  psVar9 = (short *)(param_1 + 0xa7c2f8);
  uVar6 = 0;
  local_48 = (int *)(param_1 + 0xa7c32c);
LAB_000c852c:
  piVar12 = piVar12 + 1;
  iVar4 = *piVar12;
  piVar11 = piVar11 + 1;
  iVar3 = *piVar11;
  local_4c = local_4c + 1;
  iVar14 = *local_4c;
  if (iVar4 != 0) {
    pbVar5 = (byte *)(iVar4 * 0x19);
  }
  else {
    pbVar5 = local_30;
    unaff_r5 = (int *)(uint)pbVar5[uVar8];
  }
  local_48 = local_48 + 1;
  iVar13 = *local_48;
  if (iVar4 != 0) {
    uVar7 = (int)((ulonglong)(uint)((int)pbVar5 << 2) * 0x431bde83 >> 0x20) << 6;
    unaff_r5 = (int *)(uVar7 >> 0x18);
    local_30[uVar8] = (byte)(uVar7 >> 0x18);
  }
  if (iVar14 == 0 && iVar3 == 0) {
    iVar14 = 0;
    if (iVar13 != 0) {
LAB_000c8588:
      local_30[uVar8 + 4] = (byte)((uint)(iVar13 * 100) / 1000000);
      iVar4 = iVar13;
      goto LAB_000c85a8;
    }
  }
  else {
    iVar14 = iVar14 + iVar3;
    local_30[uVar8 + 2] = (byte)((uint)(iVar14 * 100) / 1000000);
    iVar4 = iVar14;
    if (iVar13 != 0) goto LAB_000c8588;
LAB_000c85a8:
    if (iVar14 != 0) {
      bVar2 = __aeabi_uidiv(iVar3 * 100,iVar14,iVar4 * 0x36e2eb2c);
      local_30[uVar8 + 6] = bVar2;
    }
  }
  if (unaff_r5 < &DAT_00000029) {
LAB_000c8674:
    if ((0x28 < local_30[uVar8 + 4]) &&
       (uVar7 = (uint)local_30[uVar8 + 2], 0x5a < local_30[uVar8 + 4] + uVar7)) {
      bVar2 = local_30[uVar8 + 6];
      bVar16 = 0x59 < bVar2;
      bVar15 = bVar2 == 0x5a;
      if (0x5a < bVar2) {
        bVar16 = 0xe < uVar7;
        bVar15 = uVar7 == 0xf;
      }
      if (bVar16 && !bVar15) {
        if (*psVar9 == 0) {
          if (2 < DebugLevel) {
            printk("ACI detected !!!!! Apply TxOP=FE\n");
          }
          piVar10 = (int *)(param_1 + 8);
          unaff_r5 = (int *)(param_1 + 0x1a8);
          do {
            piVar10 = piVar10 + 1;
            iVar14 = *piVar10;
            if ((iVar14 != 0) && (uVar7 = HcGetBandByWdev(iVar14), uVar7 == uVar6))
            goto LAB_000c8648;
          } while (piVar10 != unaff_r5);
        }
        goto LAB_000c870c;
      }
    }
    if (*psVar9 != 0) {
      if (2 < DebugLevel) {
        printk("NO CCI /ACI detected !!!!! Apply TxOP=0\n");
      }
      piVar10 = (int *)(param_1 + 8);
      unaff_r5 = (int *)(param_1 + 0x1a8);
      do {
        piVar10 = piVar10 + 1;
        iVar14 = *piVar10;
        if ((iVar14 != 0) && (uVar7 = HcGetBandByWdev(iVar14), sVar1 = txop0, uVar7 == uVar6)) {
          *psVar9 = txop0;
          disable_tx_burst(param_1,iVar14,2,8,sVar1);
          break;
        }
      } while (piVar10 != unaff_r5);
    }
  }
  else {
    uVar7 = (uint)local_30[uVar8 + 2];
    unaff_r5 = (int *)((int)unaff_r5 + uVar7);
    if ((int)unaff_r5 < 0x5b) goto LAB_000c8674;
    bVar2 = local_30[uVar8 + 6];
    bVar16 = 0x59 < bVar2;
    bVar15 = bVar2 == 0x5a;
    if (0x5a < bVar2) {
      bVar16 = 0xe < uVar7;
      bVar15 = uVar7 == 0xf;
    }
    if (!bVar16 || bVar15) goto LAB_000c8674;
    if (*psVar9 == 0) {
      if (2 < DebugLevel) {
        printk("CCI detected !!!!! Apply TxOP=FE\n");
      }
      piVar10 = (int *)(param_1 + 8);
      unaff_r5 = (int *)(param_1 + 0x1a8);
      do {
        piVar10 = piVar10 + 1;
        iVar14 = *piVar10;
        if ((iVar14 != 0) && (uVar7 = HcGetBandByWdev(iVar14), uVar7 == uVar6)) goto LAB_000c8648;
      } while (piVar10 != unaff_r5);
    }
  }
  goto LAB_000c870c;
LAB_000c8648:
  sVar1 = txopfe;
  unaff_r5 = (int *)(param_1 + 0x1a8);
  *psVar9 = txopfe;
  enable_tx_burst(param_1,iVar14,2,8,sVar1);
LAB_000c870c:
  uVar8 = uVar8 + 1;
  psVar9 = psVar9 + 1;
  uVar6 = uVar8 & 0xff;
  if (local_40 <= uVar6) {
    return;
  }
  goto LAB_000c852c;
}

