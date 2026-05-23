// module: mt7915.ko
// function: chip_dump_mib_info @ 0x18edd4
// size: 3516 bytes
//

undefined4 chip_dump_mib_info(int param_1,int param_2)

{
  undefined1 *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  int *piVar11;
  undefined1 *puVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  undefined4 uVar18;
  uint auStack_1e0 [6];
  undefined1 auStack_1c8 [4];
  uint local_1c4;
  undefined1 *local_1c0;
  undefined1 *local_1bc;
  int local_1b8;
  int *local_1b4;
  int *local_1b0;
  undefined1 *local_1ac;
  int local_1a8;
  int local_1a4;
  int local_1a0;
  uint local_19c;
  int *local_198;
  undefined1 *local_194;
  undefined1 *local_190;
  undefined1 *local_18c;
  undefined1 *local_188;
  int *local_184;
  uint local_180;
  uint local_17c;
  uint local_178;
  uint local_174;
  uint local_170;
  uint local_16c;
  uint local_168;
  uint local_164;
  uint local_160;
  uint local_15c;
  uint local_158;
  uint local_154;
  uint local_150;
  uint local_14c;
  undefined4 local_148;
  uint local_144;
  uint local_140;
  uint local_13c;
  undefined4 local_138;
  undefined4 local_134;
  uint local_130;
  undefined4 local_12c;
  undefined4 local_128 [16];
  undefined4 local_e8 [16];
  undefined4 local_a8 [16];
  undefined4 local_68 [17];
  
  iVar13 = *(int *)(param_1 + 0x4328);
  local_1a4 = param_2;
  local_1a8 = hc_get_chip_cap(*(undefined4 *)(iVar13 + 0xa797a0));
  uVar10 = (uint)*(byte *)(local_1a8 + 0x148);
  iVar6 = (int)(short)(ushort)*(byte *)(local_1a8 + 0x148);
  uVar7 = iVar6 * 4 + 10U & 0xfffffff8;
  iVar6 = -(iVar6 * 0x10 + 8);
  local_1ac = auStack_1c8 + iVar6;
  local_188 = auStack_1c8 + (iVar6 - uVar7);
  local_18c = auStack_1c8 + uVar7 * -2 + iVar6;
  local_190 = auStack_1c8 + uVar7 * -3 + iVar6;
  local_194 = auStack_1c8 + uVar7 * -4 + iVar6;
  local_1bc = auStack_1c8 + uVar7 * -5 + iVar6;
  local_1c0 = auStack_1c8 + uVar7 * -6 + iVar6;
  if (*(char *)(local_1a8 + 0x1c4) != '\0') {
    local_198 = (int *)(&DAT_0036db38 + iVar13);
    piVar17 = (int *)0x0;
    local_1a0 = -(int)local_1ac;
    piVar11 = &DebugLevel;
    local_19c = 0;
    local_1b8 = -0x7df2a6c0;
    local_1c4 = 0xcccccccd;
    do {
      if ((local_1a4 == 0) || (uVar2 = simple_strtoul(local_1a4,0,10), uVar2 == local_19c)) {
        if ((0 < *piVar11) && (printk("Band %d MIB Status\n",local_19c), 0 < DebugLevel)) {
          printk("===============================\n");
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4c00,&local_17c);
        if (0 < *piVar11) {
          printk("MIB Status Control=0x%x\n",local_17c);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bff,&local_17c);
        if (0 < *piVar11) {
          printk("MIB Per-BSS Status Control=0x%x\n",local_17c);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf8,&local_174);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf7,&local_170);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf6,&local_16c);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf5,&local_168);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf4,&local_164);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bee,&local_160);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bed,&local_15c);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bec,&local_158);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4beb,&local_154);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bea,&local_150);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4be9,&local_14c);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf2,&local_148);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf0,&local_144);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bef,&local_140);
        local_144 = local_144 & 0xffffff;
        local_140 = local_140 & 0xffffff;
        if ((((((0 < *piVar11) && (printk("===Phy/Timing Related Counters===\n"), 0 < *piVar11)) &&
              (printk("\tChannelIdleCnt=0x%x\n",local_174 & 0xffff), 0 < *piVar11)) &&
             ((printk("\tCCA_NAV_Tx_Time=0x%x\n",local_168 & 0xffffff), 0 < *piVar11 &&
              (printk("\tRx_MDRDY_CNT=0x%x\n",local_164 & 0x3ffffff), 0 < *piVar11)))) &&
            (printk("\tCCK_MDRDY_TIME=0x%x, OFDM_MDRDY_TIME=0x%x, OFDM_GREEN_MDRDY_TIME=0x%x\n",
                    local_154 & 0xffffff,local_150 & 0xffffff,local_14c & 0xffffff), 0 < *piVar11))
           && (((printk("\tPrim CCA Time=0x%x\n",local_160 & 0xffffff), 0 < *piVar11 &&
                (printk("\tSec CCA Time=0x%x\n",local_15c & 0xffffff), 0 < *piVar11)) &&
               (printk("\tPrim ED Time=0x%x\n",local_158 & 0xffffff), 0 < *piVar11)))) {
          printk("===Tx Related Counters(Generic)===\n");
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bfc,&local_17c);
        *local_198 = *local_198 + (local_17c & 0xffff);
        if (0 < *piVar11) {
          printk("\tBeaconTxCnt=0x%x\n");
        }
        *local_198 = 0;
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bd8,&local_17c);
        if ((0 < *piVar11) && (printk("\tTx 20MHz Cnt=0x%x\n",local_17c & 0xffff), 0 < *piVar11)) {
          printk("\tTx 40MHz Cnt=0x%x\n",local_17c >> 0x10);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bd7,&local_17c);
        iVar14 = *piVar11;
        if (iVar14 < 1) {
LAB_0018f170:
          if (local_140 != 0) {
LAB_0018f17c:
            uVar2 = __aeabi_uidiv((local_144 - local_140) * 1000);
            goto LAB_0018f198;
          }
        }
        else {
          printk("\tTx 80MHz Cnt=0x%x\n",local_17c & 0xffff);
          iVar14 = *piVar11;
          if (iVar14 < 1) goto LAB_0018f170;
          printk("\tTx 160MHz Cnt=0x%x\n",local_17c >> 0x10);
          iVar14 = *piVar11;
          if (iVar14 < 1) goto LAB_0018f170;
          printk("\tAMPDU Cnt=0x%x\n",local_148);
          iVar14 = *piVar11;
          if (iVar14 < 1) goto LAB_0018f170;
          printk("\tAMPDU MPDU Cnt=0x%x\n",local_144);
          iVar14 = *piVar11;
          if (iVar14 < 1) goto LAB_0018f170;
          printk("\tAMPDU MPDU Ack Cnt=0x%x\n",local_140);
          iVar14 = *piVar11;
          uVar2 = 0;
          if (local_140 != 0) goto LAB_0018f17c;
LAB_0018f198:
          if ((0 < iVar14) &&
             (uVar3 = (uint)((ulonglong)local_1c4 * (ulonglong)uVar2 >> 0x23),
             printk("\tAMPDU MPDU PER=%ld.%1ld%%\n",uVar3,uVar2 + uVar3 * -10), 0 < *piVar11)) {
            printk("===MU Related Counters===\n");
          }
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bdc,&local_13c);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bd0,&local_138);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bcf,&local_134);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bce,&local_130);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bcd,&local_12c);
        if ((((0 < *piVar11) && (printk("\tMUBF_TX_COUNT=0x%x\n",local_13c & 0xffff), 0 < *piVar11))
            && (printk("\tMU_TX_MPDU_COUNT(Ok+Fail)=0x%x\n",local_138), 0 < *piVar11)) &&
           (((printk("\tMU_TX_OK_MPDU_COUNT=0x%x\n",local_134), 0 < *piVar11 &&
             (printk("\tMU_TO_SU_PPDU_COUNT=0x%x\n",local_130 & 0xffff), 0 < *piVar11)) &&
            ((printk("\tSU_TX_OK_MPDU_COUNT=0x%x\n",local_12c), 0 < *piVar11 &&
             ((printk("===Rx Related Counters(Generic)===\n"), 0 < *piVar11 &&
              (printk("\tVector Mismacth Cnt=0x%x\n",local_170 & 0xffff), 0 < *piVar11)))))))) {
          printk("\tDelimiter Fail Cnt=0x%x\n",local_16c & 0xffff);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bfb,&local_17c);
        if (0 < *piVar11) {
          printk("\tRxFCSErrCnt=0x%x\n",local_17c & 0xffff);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bfa,&local_17c);
        if (0 < *piVar11) {
          printk("\tRxFifoFullCnt=0x%x\n",local_17c & 0xffff);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf3,&local_17c);
        if (0 < *piVar11) {
          printk("\tRxLenMismatch=0x%x\n",local_17c & 0xffff);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bf9,&local_17c);
        if (0 < *piVar11) {
          printk("\tRxMPDUCnt=0x%x\n",local_17c);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4be8,&local_17c);
        if (0 < *piVar11) {
          printk("\tRx AMPDU Cnt=0x%x\n",local_17c);
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4be7,&local_17c);
        if (((0 < *piVar11) && (printk("\tRx Total ByteCnt=0x%x\n",local_17c), 0 < *piVar11)) &&
           (printk("===Per-BSS Related Tx/Rx Counters===\n"), 0 < *piVar11)) {
          printk("BSS Idx   TxCnt/DataCnt  TxByteCnt  RxCnt/DataCnt  RxByteCnt\n");
        }
        puVar1 = local_1bc;
        puVar12 = local_1c0;
        if (uVar10 == 0) {
          iVar14 = *piVar11;
        }
        else {
          uVar2 = 0;
          local_1b0 = piVar11;
          local_184 = piVar17;
          do {
            iVar14 = (uVar2 + 0x20835600) * 4;
            iVar15 = iVar14 + 0x7df2a800;
            uVar2 = uVar2 + 1;
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar14,local_188 + iVar15);
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar14 + 0x10,local_18c + iVar15);
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar14 + 0x20,local_190 + iVar15);
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar14 + 0x30,local_194 + iVar15);
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar14 + 0x40,puVar1 + iVar15);
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar14 + 0x50,puVar12 + iVar15);
            piVar17 = local_184;
            piVar11 = local_1b0;
          } while (uVar10 != uVar2);
          uVar2 = 0;
          iVar14 = *local_1b0;
          do {
            if (0 < iVar14) {
              uVar4 = *(undefined4 *)(local_188 + uVar2 * 4);
              uVar8 = *(undefined4 *)(local_1bc + uVar2 * 4);
              *(undefined4 *)((int)auStack_1e0 + uVar7 * -6 + iVar6) =
                   *(undefined4 *)(local_18c + uVar2 * 4);
              *(undefined4 *)((int)auStack_1e0 + uVar7 * -6 + iVar6 + 4) =
                   *(undefined4 *)(local_190 + uVar2 * 4);
              *(undefined4 *)((int)auStack_1e0 + uVar7 * -6 + iVar6 + 8) =
                   *(undefined4 *)(local_1c0 + uVar2 * 4);
              *(undefined4 *)((int)auStack_1e0 + uVar7 * -6 + iVar6 + 0xc) =
                   *(undefined4 *)(local_194 + uVar2 * 4);
              printk("%d\t 0x%x/0x%x\t 0x%x \t 0x%x/0x%x \t 0x%x\n",uVar2,uVar4,uVar8);
              iVar14 = *piVar11;
            }
            uVar2 = uVar2 + 1;
          } while (uVar10 != uVar2);
        }
        if ((0 < iVar14) && (printk("===Per-MBSS Related MIB Counters===\n"), 0 < *piVar11)) {
          printk("BSS Idx   RTSTx/RetryCnt  BAMissCnt  AckFailCnt  FrmRetry1/2/3Cnt\n");
        }
        if (uVar10 == 0) {
          iVar14 = *piVar11;
        }
        else {
          iVar14 = local_1a0 + -0x7df12f00;
          iVar16 = local_1a0 + -0x7df12efc;
          uVar2 = 0;
          local_184 = (int *)(local_1a0 + -0x7df12ef8);
          iVar15 = local_1a0 + -0x7df12ef4;
          puVar12 = local_1ac;
          local_1b4 = piVar11;
          local_1b0 = piVar17;
          do {
            uVar2 = uVar2 + 1;
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),puVar12 + iVar14,puVar12);
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),puVar12 + iVar16,puVar12 + 4);
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),
                          (undefined1 *)((int)local_184 + (int)puVar12),puVar12 + 8);
            mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),puVar12 + iVar15,puVar12 + 0xc);
            piVar17 = local_1b0;
            piVar11 = local_1b4;
            puVar12 = puVar12 + 0x10;
          } while (uVar10 != uVar2);
          uVar2 = 0;
          iVar14 = *local_1b4;
          puVar12 = local_1ac;
          do {
            if (0 < iVar14) {
              uVar5 = *(uint *)(puVar12 + 8);
              uVar3 = *(uint *)(puVar12 + 4);
              uVar9 = *(uint *)(local_1ac + uVar2 * 0x10);
              *(uint *)((int)auStack_1e0 + uVar7 * -6 + iVar6) = uVar3 & 0xffff;
              *(uint *)((int)auStack_1e0 + uVar7 * -6 + iVar6 + 4) = uVar3 >> 0x10;
              *(uint *)((int)auStack_1e0 + uVar7 * -6 + iVar6 + 8) = uVar5 & 0xffff;
              *(uint *)((int)auStack_1e0 + uVar7 * -6 + iVar6 + 0xc) = uVar5 >> 0x10;
              *(uint *)(auStack_1c8 + uVar7 * -6 + iVar6 + -8) = (uint)*(ushort *)(puVar12 + 0xc);
              printk("%d:\t0x%x/0x%x  0x%x \t 0x%x \t  0x%x/0x%x/0x%x\n",uVar2,uVar9 & 0xffff,
                     uVar9 >> 0x10);
              iVar14 = *piVar11;
            }
            uVar2 = uVar2 + 1;
            puVar12 = puVar12 + 0x10;
          } while (uVar10 != uVar2);
        }
        if (0 < iVar14) {
          printk("===Dummy delimiter insertion result===\n");
        }
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4ba8,&local_180);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bd2,&local_17c);
        mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),piVar17 + -0x1f7c4bd1,&local_178);
        uVar3 = local_17c;
        uVar2 = local_180;
        if (0 < *piVar11) {
          uVar5 = local_178 >> 0x10;
          *(uint *)((int)auStack_1e0 + uVar7 * -6 + iVar6) = local_178 & 0xffff;
          *(uint *)((int)auStack_1e0 + uVar7 * -6 + iVar6 + 4) = uVar5;
          printk("Range0 = %d\t Range1 = %d\t Range2 = %d\t Range3 = %d\t Range4 = %d\n",
                 uVar2 & 0xffff,uVar3 & 0xffff,uVar3 >> 0x10);
          if ((0 < *piVar11) && (printk("===Per-MBSS Related Tx/Rx Counters===\n"), 0 < *piVar11)) {
            printk("MBSSIdx   TxCnt  TxByteCnt  RxCnt  RxByteCnt\n");
          }
        }
        iVar14 = local_1b8;
        iVar15 = -0x7df2a700;
        do {
          mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar15,&stack0x7df2a5d8 + iVar15);
          mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar15 + 0x40,&stack0x7df2a618 + iVar15);
          mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar15 + 0x80,&stack0x7df2a658 + iVar15);
          iVar16 = iVar15 + 0xc0;
          puVar12 = &stack0x7df2a698 + iVar15;
          iVar15 = iVar15 + 4;
          mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar16,puVar12);
        } while (iVar15 != iVar14);
        iVar14 = 0;
        do {
          if (0 < *piVar11) {
            uVar18 = local_68[iVar14];
            uVar4 = local_128[iVar14];
            uVar8 = local_e8[iVar14];
            *(undefined4 *)((int)auStack_1e0 + uVar7 * -6 + iVar6) = local_a8[iVar14];
            *(undefined4 *)((int)auStack_1e0 + uVar7 * -6 + iVar6 + 4) = uVar18;
            printk("%d\t 0x%x\t 0x%x \t 0x%x \t 0x%x\n",iVar14,uVar4,uVar8);
          }
          iVar14 = iVar14 + 1;
        } while (iVar14 != 0x10);
      }
      piVar17 = piVar17 + 0x4000;
      local_19c = local_19c + 1;
      local_198 = local_198 + 3;
      local_1a0 = local_1a0 + 0x10000;
    } while (local_19c < *(byte *)(local_1a8 + 0x1c4));
  }
  return 1;
}

