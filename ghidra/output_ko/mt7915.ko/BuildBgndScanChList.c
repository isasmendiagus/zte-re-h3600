// module: mt7915.ko
// function: BuildBgndScanChList @ 0x22d210
// size: 1444 bytes
//

void BuildBgndScanChList(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  byte *pbVar10;
  uint uVar11;
  int iVar12;
  byte *pbVar13;
  char *pcVar14;
  uint uVar15;
  undefined1 *puVar16;
  int iVar17;
  bool bVar18;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: NULL wdev, band idx = %d\n","BuildBgndScanChList");
    return;
  }
  uVar5 = HcGetBandByWdev(param_2);
  iVar6 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar5);
  bVar18 = (*(ushort *)(param_2 + 0x18) & 0xb1) != 0;
  iVar7 = wlan_config_get_ht_bw(param_2);
  iVar8 = wlan_config_get_vht_bw(param_2);
  os_zero_mem(param_1 + 0xa78ad4,0x588);
  *(undefined1 *)(param_1 + 0xa78ad1) = 0;
  if (bVar18) {
    if (iVar8 == 1) {
      *(undefined1 *)(param_1 + 0xa78ad0) = 2;
    }
    else {
      *(char *)(param_1 + 0xa78ad0) = (char)iVar7;
    }
    uVar11 = (uint)*(byte *)(iVar6 + 0x49c);
    if (uVar11 != 0) {
      uVar15 = 0;
      puVar16 = (undefined1 *)(iVar6 + 5);
      iVar17 = 0;
      pbVar10 = (byte *)(param_1 + 0xa79756);
LAB_0022d300:
      bVar1 = puVar16[-5];
      if (iVar7 != 0) {
        if (iVar8 != 0 || iVar7 != 1) {
          if (iVar8 == 1) {
            iVar12 = vht80_channel_group(param_1,bVar1,param_2);
            if (iVar12 != 0) {
              uVar9 = wlan_config_get_ch_band(param_2);
              iVar12 = param_1 + uVar15 * 0x18;
              *(undefined1 *)(iVar12 + 0xa78ad5) = puVar16[-5];
              uVar4 = vht_cent_ch_freq(bVar1,1,uVar9);
              *(undefined1 *)(iVar12 + 0xa78ad6) = uVar4;
              *(undefined1 *)(iVar12 + 0xa78ad7) = *puVar16;
              uVar4 = 0;
              if (*(char *)(param_1 + 0xa79755) != '\0') {
                if (*(byte *)(param_1 + 0xa79756) != bVar1) {
                  pbVar13 = pbVar10;
                  do {
                    if (pbVar13 ==
                        (byte *)(param_1 + (byte)(*(char *)(param_1 + 0xa79755) - 1) + 0xa79756))
                    goto LAB_0022d5f4;
                    pbVar13 = pbVar13 + 1;
                  } while (*pbVar13 != bVar1);
                }
                goto LAB_0022d618;
              }
              goto LAB_0022d5f8;
            }
            goto LAB_0022d4e0;
          }
          goto LAB_0022d3ac;
        }
        iVar12 = N_ChannelGroupCheck(param_1,bVar1,param_2);
        if (iVar12 != 0) {
          iVar12 = param_1 + uVar15 * 0x18;
          *(undefined1 *)(iVar12 + 0xa78ad5) = puVar16[-5];
          if ((((bVar1 & 0xe7) == 0x24) || ((bVar1 & 0xe7) == 100)) ||
             ((bVar1 & 0xf7) == 0x95 || bVar1 == 0x84)) {
            *(char *)(param_1 + uVar15 * 0x18 + 0xa78ad6) = puVar16[-5] + '\x02';
          }
          else {
            *(char *)(iVar12 + 0xa78ad6) = puVar16[-5] + -2;
          }
          *(undefined1 *)(param_1 + uVar15 * 0x18 + 0xa78ad7) = *puVar16;
          uVar4 = 0;
          if (*(char *)(param_1 + 0xa79755) != '\0') {
            if (*(byte *)(param_1 + 0xa79756) != bVar1) {
              pbVar13 = pbVar10;
              do {
                if (pbVar13 ==
                    (byte *)(param_1 + (byte)(*(char *)(param_1 + 0xa79755) - 1) + 0xa79756))
                goto LAB_0022d5f4;
                pbVar13 = pbVar13 + 1;
              } while (*pbVar13 != bVar1);
            }
LAB_0022d618:
            uVar4 = 1;
          }
          goto LAB_0022d5f8;
        }
        goto LAB_0022d4e0;
      }
      iVar12 = param_1 + uVar15 * 0x18;
      *(byte *)(iVar12 + 0xa78ad5) = bVar1;
      *(undefined1 *)(iVar12 + 0xa78ad6) = puVar16[-5];
      *(undefined1 *)(iVar12 + 0xa78ad7) = *puVar16;
      if (*(char *)(param_1 + 0xa79755) == '\0') {
LAB_0022d384:
        uVar4 = 0;
      }
      else {
        if (*(byte *)(param_1 + 0xa79756) != bVar1) {
          pbVar13 = pbVar10;
          do {
            if (pbVar13 == (byte *)(param_1 + (byte)(*(char *)(param_1 + 0xa79755) - 1) + 0xa79756))
            goto LAB_0022d384;
            pbVar13 = pbVar13 + 1;
          } while (*pbVar13 != bVar1);
        }
        uVar4 = 1;
      }
      *(undefined1 *)(param_1 + uVar15 * 0x18 + 0xa78ad9) = uVar4;
      uVar11 = (uint)*(byte *)(iVar6 + 0x49c);
      uVar15 = uVar15 + 1;
      goto LAB_0022d3ac;
    }
LAB_0022d76c:
    iVar6 = DebugLevel;
    if (2 < DebugLevel) {
      uVar11 = 0;
      uVar15 = 0;
LAB_0022d794:
      printk("BandIdx=%d, IsABand=%d, ScanBW=%d\n",uVar5,bVar18,*(undefined1 *)(param_1 + 0xa78ad0))
      ;
      goto LAB_0022d3d4;
    }
    uVar15 = 0;
    *(undefined1 *)(param_1 + 0xa78ad1) = 0;
  }
  else {
    *(bool *)(param_1 + 0xa78ad0) = bVar18;
    if (*(char *)(iVar6 + 0x49c) == '\0') goto LAB_0022d76c;
    cVar2 = *(char *)(param_1 + 0xa79755);
    puVar16 = (undefined1 *)(param_1 + 0xa78ad6);
    uVar15 = 0;
    iVar7 = 0;
    do {
      uVar4 = *(undefined1 *)(iVar6 + iVar7);
      *puVar16 = uVar4;
      puVar16[-1] = uVar4;
      if (cVar2 == '\0') {
LAB_0022d488:
        uVar4 = 0;
      }
      else {
        cVar3 = *(char *)(param_1 + 0xa79756);
        pcVar14 = (char *)(param_1 + 0xa79756);
        while (cVar3 != *(char *)(iVar6 + iVar7)) {
          if (pcVar14 == (char *)(param_1 + (byte)(cVar2 - 1) + 0xa79756)) goto LAB_0022d488;
          pcVar14 = pcVar14 + 1;
          cVar3 = *pcVar14;
        }
        uVar4 = 1;
      }
      puVar16[3] = uVar4;
      uVar15 = uVar15 + 1;
      iVar7 = iVar7 + 0x14;
      puVar16 = puVar16 + 0x18;
    } while ((int)uVar15 < (int)(uint)*(byte *)(iVar6 + 0x49c));
LAB_0022d3bc:
    uVar11 = uVar15 & 0xff;
    if (2 < DebugLevel) goto LAB_0022d794;
LAB_0022d3d4:
    *(char *)(param_1 + 0xa78ad1) = (char)uVar11;
    iVar6 = DebugLevel;
    if (uVar11 != 0) goto LAB_0022d6f4;
  }
  if (iVar6 < 0) {
    return;
  }
  printk("[%s] BandIdx = %d, pAd->BgndScanCtrl.ChannelListNum=%d\n","BuildBgndScanChList",uVar5,
         uVar15);
  if (*(char *)(param_1 + 0xa78ad1) == '\0') {
    return;
  }
LAB_0022d6f4:
  iVar6 = 0;
  puVar16 = (undefined1 *)(param_1 + 0xa78ad5);
  do {
    iVar6 = iVar6 + 1;
    if (2 < DebugLevel) {
      printk("Support channel: PrimCh=%d, CentCh=%d, DFS=%d\n",*puVar16,puVar16[1],puVar16[2]);
    }
    puVar16 = puVar16 + 0x18;
  } while (iVar6 < (int)(uint)*(byte *)(param_1 + 0xa78ad1));
  return;
LAB_0022d5f4:
  uVar4 = 0;
LAB_0022d5f8:
  *(undefined1 *)(param_1 + uVar15 * 0x18 + 0xa78ad9) = uVar4;
  uVar15 = uVar15 + 1;
LAB_0022d4e0:
  uVar11 = (uint)*(byte *)(iVar6 + 0x49c);
LAB_0022d3ac:
  iVar17 = iVar17 + 1;
  puVar16 = puVar16 + 0x14;
  if ((int)uVar11 <= iVar17) goto LAB_0022d3bc;
  goto LAB_0022d300;
}

