// module: mt7915.ko
// function: mtf_dump_txs @ 0x19ce3c
// size: 508 bytes
//

void mtf_dump_txs(undefined4 param_1,int param_2,byte *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_2 != 0) {
    if (param_2 == 1) {
      if (0 < DebugLevel) {
        printk("\tType=Noisy/RCPI Mode\n");
        return;
      }
      return;
    }
    if (0 < DebugLevel) {
      printk("%s: Unknown TxSFormat(%d)\n","mtf_dump_txs",param_2);
      return;
    }
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("\tType=TimeStamp/FrontTime Mode\n");
  if (0 < DebugLevel) {
    uVar3 = (uint)param_3[1];
    printk("\t\tTXSFM=%d, TXS2M/H=%d/%d, FixRate=%d, TxRate/BW=0x%x/%d\n",(uVar3 << 0x1a) >> 0x1f,
           (uVar3 << 0x19) >> 0x1f,param_3[1] >> 7,(uVar3 << 0x1b) >> 0x1f,
           (uint)*param_3 | (uVar3 & 0xf) << 8,param_3[5] >> 6);
    if (DebugLevel < 1) {
      return;
    }
    uVar5 = (uint)param_3[3];
    uVar4 = (uint)param_3[2];
    uVar1 = (uVar4 << 0x1b) >> 0x1f;
    uVar3 = (uVar4 << 0x19) >> 0x1f;
    uVar2 = (uVar4 << 0x1a) >> 0x1f;
    printk("\t\tME/RE/LE/BE/TxOPLimitErr/BA-Fail=%d/%d/%d/%d/%d/%d, PS=%d, Pid=%d\n",uVar4 & 1,
           (uVar4 << 0x1e) >> 0x1f,(uVar4 << 0x1d) >> 0x1f,(uVar4 << 0x1c) >> 0x1f,uVar1,uVar3,uVar2
           ,uVar5);
    if (DebugLevel < 1) {
      return;
    }
    uVar4 = (uint)param_3[5];
    uVar6 = (uVar4 << 0x1a) >> 0x1f;
    printk("\t\tTid=%d, AntId=%d, ETxBF/ITxBf=%d/%d\n",(uVar4 << 0x1c) >> 0x1d,
           (uint)param_3[7] << 4 | (uint)(param_3[6] >> 4),(uVar4 << 0x1b) >> 0x1f,uVar6,uVar1,uVar3
           ,uVar2,uVar5);
    if (DebugLevel < 1) {
      return;
    }
    printk("\t\tTxPwrdBm=0x%x, FinalMPDU=0x%x, AMPDU=0x%x\n",param_3[4] & 0x7f,param_3[4] >> 7,
           param_3[5] & 1,uVar6,uVar1,uVar3,uVar2,uVar5);
  }
  if ((0 < DebugLevel) &&
     (printk("\t\tTxDelay=0x%x, RxVSeqNum=0x%x, Wlan Idx=0x%x\n",*(undefined2 *)(param_3 + 8),
             param_3[10],param_3[0xb]), 0 < DebugLevel)) {
    printk("\t\tSN=0x%x, MPDU TxCnt=%d, LastTxRateIdx=%d\n",
           (uint)param_3[0xc] | (param_3[0xd] & 0xf) << 8,param_3[0xf] & 0x1f,param_3[0xf] >> 5);
    return;
  }
  return;
}

