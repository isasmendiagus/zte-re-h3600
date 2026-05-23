// module: mt7915.ko
// function: assoc_ht_info_debugshow @ 0xe977c
// size: 936 bytes
//

void assoc_ht_info_debugshow(undefined4 param_1,int param_2,byte *param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_3 == (byte *)0x0) {
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("Peer - 11n HT Info\n");
  if (DebugLevel < 3) {
LAB_000e9878:
    if (2 < DebugLevel) {
      printk("\tHT Parm Info:\n");
      if (DebugLevel < 3) {
        return;
      }
      printk("\t\t MaxRx A-MPDU Factor(%d), MPDU Density(%d)\n",param_3[2] & 3,
             ((uint)param_3[2] << 0x1b) >> 0x1d);
      goto LAB_000e98bc;
    }
LAB_000e9928:
    if (2 < DebugLevel) {
      printk("\tExt HT Cap Info:\n");
      if (DebugLevel < 3) {
        return;
      }
      uVar2 = (uint)param_3[0x14];
      printk("\t\t PCO(%d), TransTime(%d), MCSFeedback(%d), +HTC(%d), RDG(%d)\n",param_3[0x13] & 1,
             ((uint)param_3[0x13] << 0x1d) >> 0x1e,uVar2 & 3,(uVar2 << 0x1d) >> 0x1f,
             (uVar2 << 0x1c) >> 0x1f);
      goto LAB_000e9984;
    }
LAB_000e99e4:
    if (DebugLevel < 3) goto LAB_000e9b00;
    uVar2 = (uint)param_3[0x16];
    printk("\t\t Calibration(%d), ExpCSICapable(%d), ExpComSteerCapable(%d), ExpCSIFbk(%d), ExpNoComBF(%d) ExpComBF(%d)\n"
           ,param_3[0x15] >> 6,uVar2 & 1,(uVar2 << 0x1d) >> 0x1f,(uVar2 << 0x1b) >> 0x1e,
           (uVar2 << 0x19) >> 0x1e,(param_3[0x17] & 1) << 1 | param_3[0x16] >> 7);
    if (DebugLevel < 3) {
      return;
    }
    uVar2 = (uint)param_3[0x18];
    uVar3 = (uint)param_3[0x17];
    printk("\t\t MinGrouping(%d), CSIBFAntSup(%d), NoComSteerBFAntSup(%d), ComSteerBFAntSup(%d), CSIRowBFSup(%d) ChanEstimation(%d)\n"
           ,(uVar3 << 0x1d) >> 0x1e,(uVar3 << 0x1b) >> 0x1e,(uVar3 << 0x19) >> 0x1e,
           (uVar2 & 1) << 1 | (uint)(param_3[0x17] >> 7),(uVar2 << 0x1d) >> 0x1e,
           (uVar2 << 0x1b) >> 0x1e);
  }
  else {
    printk("\tHT Cap Info:\n");
    if (DebugLevel < 3) {
      return;
    }
    uVar3 = (uint)*param_3;
    uVar2 = (uVar3 << 0x19) >> 0x1f;
    printk("\t\t HT_RX_LDPC(%d), BW(%d), MIMOPS(%d), GF(%d), ShortGI_20(%d), ShortGI_40(%d)\n",
           uVar3 & 1,(uVar3 << 0x1e) >> 0x1f,(uVar3 << 0x1c) >> 0x1e,(uVar3 << 0x1b) >> 0x1f,
           (uVar3 << 0x1a) >> 0x1f,uVar2);
    if (2 < DebugLevel) {
      uVar4 = (uint)param_3[1];
      uVar3 = (uVar4 << 0x1c) >> 0x1f;
      uVar5 = (uVar4 << 0x1b) >> 0x1f;
      printk("\t\t TxSTBC(%d), RxSTBC(%d), DelayedBA(%d), A-MSDU(%d), CCK_40(%d)\n",*param_3 >> 7,
             uVar4 & 3,(uVar4 << 0x1d) >> 0x1f,uVar3,uVar5,uVar2);
      if (DebugLevel < 3) {
        return;
      }
      bVar1 = param_3[1];
      printk("\t\t PSMP(%d), Forty_Mhz_Intolerant(%d), L-SIG(%d)\n",((uint)bVar1 << 0x1a) >> 0x1f,
             ((uint)bVar1 << 0x19) >> 0x1f,bVar1 >> 7,uVar3,uVar5,uVar2);
      goto LAB_000e9878;
    }
LAB_000e98bc:
    if (2 < DebugLevel) {
      printk("\tHT MCS set:\n");
      if (DebugLevel < 3) {
        return;
      }
      printk("\t\t RxMCS(%02x %02x %02x %02x %02x) MaxRxMbps(%d) TxMCSSetDef(%02x)\n",param_3[3],
             param_3[4],param_3[5],param_3[6],param_3[7],
             (uint)param_3[0xd] + (uint)param_3[0xe] * 0x100,param_3[0xf]);
      goto LAB_000e9928;
    }
LAB_000e9984:
    if (2 < DebugLevel) {
      printk("\tTX BF Cap:\n");
      if (DebugLevel < 3) {
        return;
      }
      uVar2 = (uint)param_3[0x15];
      printk("\t\t ImpRxCap(%d), RXStagSnd(%d), TXStagSnd(%d), RxNDP(%d), TxNDP(%d) ImpTxCap(%d)\n",
             uVar2 & 1,(uVar2 << 0x1e) >> 0x1f,(uVar2 << 0x1d) >> 0x1f,(uVar2 << 0x1c) >> 0x1f,
             (uVar2 << 0x1b) >> 0x1f,(uVar2 << 0x1a) >> 0x1f);
      goto LAB_000e99e4;
    }
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("\nPeer - MODE=%d, BW=%d, MCS=%d, ShortGI=%d, MaxRxFactor=%d, MpduDensity=%d, MIMOPS=%d, AMSDU=%d\n"
         ,*(byte *)(param_2 + 0xbd) >> 5,((uint)*(ushort *)(param_2 + 0xbc) << 0x17) >> 0x1e,
         *(byte *)(param_2 + 0xbc) & 0x3f,((uint)*(byte *)(param_2 + 0xbd) << 0x1e) >> 0x1f,
         *(undefined1 *)(param_2 + 0xd05),*(undefined1 *)(param_2 + 0xd04),
         *(undefined1 *)(param_2 + 0xd10),*(undefined1 *)(param_2 + 0xd06));
  if (DebugLevel < 3) {
    return;
  }
  printk("\tExt Cap Info:\n");
LAB_000e9b00:
  if (DebugLevel < 3) {
    return;
  }
  printk("\t\tBss2040CoexistMgmt=%d\n",*(undefined1 *)(param_2 + 0xd11));
  return;
}

