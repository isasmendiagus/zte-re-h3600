// module: mt7915.ko
// function: mtf_txs_handler @ 0x1a081c
// size: 1584 bytes
//

undefined4 mtf_txs_handler(int *param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  int iVar11;
  int iVar12;
  
  uVar4 = (*param_2 << 0xb) >> 0x1b;
  uVar7 = *param_2 & 0xffff;
  if ((2 < DebugLevel) &&
     (printk("%s[%d] start=====================>\n","mtf_txs_handler",
             *(uint *)(*param_1 + 0x3c) & 0xff), 3 < DebugLevel)) {
    printk("\tTxS Report: Number=%d, ByteCnt=%d\n",uVar4,uVar7);
  }
  if (uVar7 == 0) {
    return 1;
  }
  if (uVar4 * 0x20 + 8 == uVar7) {
    puVar5 = param_2 + 2;
    if (uVar4 != 0) {
      do {
        uVar4 = *puVar5;
        uVar6 = (uVar4 << 7) >> 0x1e;
        if (2 < DebugLevel) {
          printk("\t\tTXSFM = %d, TXS2M/H = %d/%d, FixRate = %d, TxRate/BW = 0x%x/%d\n",uVar6,
                 (uVar4 << 0x11) >> 0x1f,(uVar4 << 0x10) >> 0x1f,uVar4 >> 0x1f,uVar4 & 0x3fff,
                 (uVar4 << 1) >> 0x1e);
          uVar4 = *puVar5;
        }
        iVar2 = DebugLevel;
        uVar1 = (uVar4 << 3) >> 0x1d;
        if ((int)(uVar4 << 0xf) < 0) {
          param_1[uVar1 + 0x276ec] = param_1[uVar1 + 0x276ec] + 1;
          uVar4 = *puVar5;
        }
        if ((int)(uVar4 << 0xe) < 0) {
          param_1[uVar1 + 0x276f4] = param_1[uVar1 + 0x276f4] + 1;
          uVar4 = *puVar5;
        }
        if ((int)(uVar4 << 0xd) < 0) {
          param_1[uVar1 + 0x276fc] = param_1[uVar1 + 0x276fc] + 1;
          uVar4 = *puVar5;
        }
        uVar9 = -((int)(uVar4 << 0xc) >> 0x1f);
        if (uVar9 != 0) {
          param_1[uVar1 + 0x27704] = param_1[uVar1 + 0x27704] + 1;
          uVar4 = *puVar5;
        }
        iVar8 = -((int)(uVar4 << 0xb) >> 0x1f);
        if (iVar8 != 0) {
          param_1[uVar1 + 0x2770c] = param_1[uVar1 + 0x2770c] + 1;
          uVar4 = *puVar5;
        }
        iVar3 = -((int)(uVar4 << 9) >> 0x1f);
        if (iVar3 != 0) {
          param_1[uVar1 + 0x27714] = param_1[uVar1 + 0x27714] + 1;
        }
        if (iVar2 < 3) {
LAB_001a09c4:
          if ((1 < uVar6) && (uVar6 != 2)) {
LAB_001a09d4:
            if (2 < iVar2) {
              printk("%s: Unknown TxSFormat(%d)\n","mtf_txs_handler",uVar6);
              goto LAB_001a0d50;
            }
          }
        }
        else {
          uVar4 = puVar5[3] >> 0x18;
          uVar1 = (*puVar5 << 10) >> 0x1f;
          iVar11 = iVar8;
          iVar12 = iVar3;
          printk("\t\tME/RE/LE/BE/TxOPLimitErr/BA-Fail = %d/%d/%d/%d/%d/%d, PS = %d, Pid = %d\n");
          if (DebugLevel < 3) {
LAB_001a0cb0:
            iVar2 = DebugLevel;
            if (DebugLevel < 3) goto LAB_001a09c4;
            printk("\t\ttimestamp = 0x%x\n",puVar5[4]);
LAB_001a0cd4:
            if (1 < uVar6) goto LAB_001a0cdc;
            if (DebugLevel < 3) goto LAB_001a09dc;
            uVar9 = puVar5[5];
            printk("\t\tFrontTime(32us) = 0x%x, MPDU TxCnt =%d, Oos = %d, FinalMPDU = %d\n",
                   uVar9 & 0x1ffffff,(uVar9 << 2) >> 0x1b,(uVar9 << 1) >> 0x1f,uVar9 >> 0x1f,iVar11,
                   iVar12,uVar1,uVar4);
LAB_001a0d50:
            if (2 < DebugLevel) {
              printk(&_LC288);
            }
          }
          else {
            uVar9 = puVar5[2] >> 0x1f;
            printk("\t\tTid = %d, AntId = %d, ETxBF/ITxBf = %d/%d\n",(*puVar5 << 3) >> 0x1d,
                   puVar5[3] & 0xffffff,(puVar5[2] << 1) >> 0x1f,uVar9,iVar11,iVar12,uVar1,uVar4);
            if (2 < DebugLevel) {
              printk("\t\tTxPwrdBm = 0x%x, AMPDU = 0x%x\n",puVar5[1] & 0xff,(*puVar5 << 6) >> 0x1f);
              if (2 < DebugLevel) {
                printk("\t\tTxDelay(32us) = 0x%x, RxVSeqNum =0x %x, Wlan Idx = 0x%x\n",
                       puVar5[2] & 0xffff,(puVar5[1] << 0x10) >> 0x18,(puVar5[2] << 6) >> 0x16,uVar9
                       ,iVar11,iVar12,uVar1,uVar4);
                iVar2 = DebugLevel;
                if (DebugLevel < 3) goto LAB_001a09c4;
                printk("\t\tSN = 0x%x, LastTxRateIdx = %d\n",puVar5[1] >> 0x14,
                       (puVar5[2] << 2) >> 0x1d);
                goto LAB_001a0cb0;
              }
              goto LAB_001a0cd4;
            }
            if (1 < uVar6) {
LAB_001a0cdc:
              iVar2 = DebugLevel;
              if (uVar6 != 2) goto LAB_001a09d4;
              if (((2 < DebugLevel) &&
                  (printk("\t\tPPDU MPDU TX Bytes = %d, PPDU MPDU TX Cnt = %d\n",
                          puVar5[5] & 0xffffff,puVar5[5] >> 0x18), 2 < DebugLevel)) &&
                 (printk("\t\tPPDU MPDU Fail Bytes = %d, PPDU MPDU Fail Cnt = %d\n",
                         puVar5[6] & 0xffffff,puVar5[6] >> 0x18,DebugLevel,uVar9,iVar11,iVar12,uVar1
                         ,uVar4), 2 < DebugLevel)) {
                printk("\t\tPPDU MPDU Retry Bytes = %d, PPDU MPDU Retry Cnt = %d\n",
                       puVar5[7] & 0xffffff,puVar5[7] >> 0x18,DebugLevel,uVar9);
                goto LAB_001a0d50;
              }
            }
          }
        }
LAB_001a09dc:
        uVar4 = (puVar5[2] << 6) >> 0x16;
        iVar2 = wdev_search_by_wcid(param_1,uVar4);
        if (((*(char *)((int)param_1 + (uint)*(byte *)(iVar2 + 0xc) * 0x5834 + 0x2bca4b) != '\0') &&
            (uVar1 = HcGetMaxStaNum(param_1), uVar4 < uVar1)) &&
           ((param_1 + uVar4 * 0x530 + 0x28748 != (int *)0x0 &&
            (param_1[uVar4 * 0x530 + 0x28748] != 0)))) {
          puVar10 = (uint *)param_1[uVar4 * 0x530 + 0x28c74];
          if (puVar10 == (uint *)0x0) {
            _raw_spin_lock_bh(param_1 + 0xa1656);
            ZTE_tx_ctrl_rate_stat_init(param_1,param_1 + uVar4 * 0x530 + 0x28748);
            _raw_spin_unlock_bh(param_1 + 0xa1656);
            puVar10 = (uint *)param_1[uVar4 * 0x530 + 0x28c74];
            if (puVar10 == (uint *)0x0) goto LAB_001a08c4;
          }
          uVar4 = *puVar10;
          *puVar10 = uVar4 + 1;
          puVar10[1] = puVar10[1] + (uint)(0xfffffffe < uVar4);
          if (iVar8 != 0) {
            uVar4 = puVar10[2];
            puVar10[2] = uVar4 + 1;
            puVar10[3] = puVar10[3] + (uint)(0xfffffffe < uVar4);
          }
          if (iVar3 != 0) {
            uVar4 = puVar10[4];
            puVar10[4] = uVar4 + 1;
            puVar10[5] = puVar10[5] + (uint)(0xfffffffe < uVar4);
          }
          if (uVar6 < 2) {
            uVar6 = puVar10[6];
            uVar4 = (puVar5[5] << 2) >> 0x1b;
            puVar10[6] = uVar6 + uVar4;
            puVar10[7] = puVar10[7] + (uint)CARRY4(uVar6,uVar4);
          }
          else if (uVar6 == 2) {
            uVar4 = puVar5[5];
            uVar6 = puVar10[8];
            puVar10[8] = uVar6 + (uVar4 & 0xffffff);
            puVar10[9] = puVar10[9] + (uint)CARRY4(uVar6,uVar4 & 0xffffff);
            uVar4 = puVar5[5];
            uVar6 = puVar10[6];
            puVar10[6] = uVar6 + (uVar4 >> 0x18);
            puVar10[7] = puVar10[7] + (uint)CARRY4(uVar6,uVar4 >> 0x18);
            uVar4 = puVar5[6];
            uVar6 = puVar10[10];
            puVar10[10] = uVar6 + (uVar4 >> 0x18);
            puVar10[0xb] = puVar10[0xb] + (uint)CARRY4(uVar6,uVar4 >> 0x18);
            uVar4 = puVar5[7];
            uVar6 = puVar10[0xc];
            puVar10[0xc] = uVar6 + (uVar4 >> 0x18);
            puVar10[0xd] = puVar10[0xd] + (uint)CARRY4(uVar6,uVar4 >> 0x18);
          }
          ZTE_tx_ctrl_rate(puVar10 + 0xe,(*puVar5 << 1) >> 0x1e | (*puVar5 & 0x3fff) << 2);
        }
LAB_001a08c4:
        puVar5 = puVar5 + 8;
      } while (puVar5 != (uint *)((int)param_2 + uVar7));
    }
  }
  else {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("ReceivedByteCnt not equal txs_entry required!\n");
  }
  if (DebugLevel < 3) {
    return 0;
  }
  printk("%s end<=====================\n","mtf_txs_handler");
  return 0;
}

