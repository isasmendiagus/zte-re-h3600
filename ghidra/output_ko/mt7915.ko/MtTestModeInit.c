// module: mt7915.ko
// function: MtTestModeInit @ 0x28a9ec
// size: 1460 bytes
//

int MtTestModeInit(int param_1)

{
  int iVar1;
  code *pcVar2;
  undefined4 *puVar3;
  undefined4 *local_2c [2];
  
  local_2c[0] = (undefined4 *)0x0;
  iVar1 = os_alloc_mem(param_1,local_2c,4);
  if (iVar1 == 0) {
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915 ||
        (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x6867) {
      pcVar2 = mt_ate_fill_offload_tx_blk;
    }
    else {
      pcVar2 = mt_ate_fill_non_offload_tx_blk;
    }
    *local_2c[0] = pcVar2;
    *(undefined4 **)(param_1 + 0xa39fd0) = local_2c[0];
  }
  local_2c[0] = (undefined4 *)0x0;
  iVar1 = os_alloc_mem(param_1,local_2c,0x128);
  if (iVar1 == 0) {
    *local_2c[0] = MT_ATEStart;
    local_2c[0][1] = MT_ATEStop;
    local_2c[0][4] = MT_ATEStartTx;
    local_2c[0][5] = MT_ATEStartRx;
    local_2c[0][6] = MT_ATEStopTx;
    local_2c[0][7] = MT_ATEStopRx;
    local_2c[0][10] = MT_ATESetRxUserIdx;
    local_2c[0][0xb] = MT_ATESetTxPower0;
    local_2c[0][0xc] = MT_ATESetTxPower1;
    local_2c[0][0xd] = MT_ATESetTxPower2;
    local_2c[0][0xe] = MT_ATESetTxPower3;
    local_2c[0][0xf] = MT_ATESetForceTxPower;
    local_2c[0][0x10] = MT_ATESetTxPowerX;
    local_2c[0][0x11] = MT_ATESetTxAntenna;
    local_2c[0][0x12] = MT_ATESetRxAntenna;
    local_2c[0][0x13] = MT_ATESetTxFreqOffset;
    local_2c[0][0x14] = MT_ATEGetTxFreqOffset;
    local_2c[0][0x15] = MT_ATESetChannel;
    local_2c[0][0x16] = MT_ATESetBW;
    local_2c[0][0x17] = mt_ate_set_duty_cycle;
    local_2c[0][0x18] = mt_ate_set_pkt_tx_time;
    local_2c[0][0x2e] = MtATE_Group_Pre_Cal_Store_Proc_7915;
    local_2c[0][0x2f] = MtATE_DPD_Cal_Store_Proc_7915;
    local_2c[0][0x19] = MT_ATESampleRssi;
    local_2c[0][0x32] = MtATE_DNL_Cal_Store_Proc_7915;
    local_2c[0][0x1a] = mt_ate_set_ipg;
    local_2c[0][0x1b] = mt_ate_set_slot_time;
    local_2c[0][0x1c] = MT_ATESetAIFS;
    local_2c[0][0x1d] = MT_ATESetPowerDropLevel;
    local_2c[0][0x1e] = MT_ATESetTSSI;
    local_2c[0][0x1f] = MT_ATELowPower;
    local_2c[0][0x20] = MT_ATESetEepromToFw;
    local_2c[0][0x21] = MT_ATESetDPD;
    local_2c[0][0x22] = MT_ATEStartTxTone;
    local_2c[0][0x3c] = MT_ATEDBDCTxTone;
    local_2c[0][0x24] = MT_ATESetDBDCTxTonePower;
    local_2c[0][0x25] = MT_ATEGetDBDCTxTonePower;
    local_2c[0][0x23] = MT_ATESetTxTonePower;
    local_2c[0][0x26] = MT_ATEStopTxTone;
    local_2c[0][0x27] = MT_ATEStartContinousTx;
    local_2c[0][0x28] = MT_ATEStopContinousTx;
    local_2c[0][0x2b] = MT_RfRegWrite;
    local_2c[0][0x2c] = MT_RfRegRead;
    local_2c[0][0x29] = MT_EfuseGetFreeBlock;
    local_2c[0][0x2d] = MT_GetFWInfo;
    local_2c[0][0x30] = MT_SetATESoundingProc;
    local_2c[0][0x31] = MT_ATEStartTxSKB;
    local_2c[0][0x42] = MT_ATESetICapStart;
    local_2c[0][0x43] = MT_ATEGetICapStatus;
    local_2c[0][0x44] = MT_ATEGetICapIQData;
    local_2c[0][0x47] = mt_ate_off_ch_scan;
    local_2c[0][0x33] = MT_MPSSetParm;
    local_2c[0][0x34] = MT_MPSTxStart;
    local_2c[0][0x35] = MT_MPSTxStop;
    local_2c[0][0x36] = MT_ATESetAutoResp;
    local_2c[0][0x37] = MT_SetFFTMode;
    local_2c[0][0x38] = MT_OnOffRDD;
    local_2c[0][0x39] = MT_ATESetCfgOnOff;
    local_2c[0][0x3a] = MT_ATEGetCfgOnOff;
    local_2c[0][0x3b] = MT_ATESetRXFilterPktLen;
    local_2c[0][0x3d] = MT_ATEGetTxPower;
    local_2c[0][0x3e] = MT_ATEBssInfoUpdate;
    local_2c[0][0x3f] = MT_ATEDevInfoUpdate;
    local_2c[0][0x40] = MT_ATELogOnOff;
    local_2c[0][0x45] = MT_ATESetAntennaPort;
    local_2c[0][0x46] = MT_ATEFWPacketCMDClockSwitchDisable;
    local_2c[0][0x48] = mt_ate_show_ru_info;
    local_2c[0][0x49] = mt_ate_set_ru_info;
    local_2c[0][2] = mt_ate_tx_subscribe;
    local_2c[0][3] = mt_ate_tx_unsubscribe;
    *(undefined4 **)(param_1 + 0xa39fd4) = local_2c[0];
  }
  local_2c[0] = (undefined4 *)0x0;
  iVar1 = os_alloc_mem(param_1,local_2c,0x18);
  if (iVar1 == 0) {
    if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) {
      *local_2c[0] = pci_ate_init;
      local_2c[0][2] = 0;
      local_2c[0][3] = 0;
      local_2c[0][4] = 0;
      local_2c[0][1] = pci_clean_q;
      local_2c[0][5] = pci_ate_leave;
    }
    else {
      *local_2c[0] = 0;
      local_2c[0][1] = 0;
      local_2c[0][2] = 0;
      local_2c[0][3] = 0;
      local_2c[0][4] = 0;
      local_2c[0][5] = 0;
    }
    *(undefined4 **)(param_1 + 0xa39fd8) = local_2c[0];
  }
  *(undefined4 *)(param_1 + 0xa3abcc) = 0;
  RtmpOSTaskInit(param_1 + 0xa77b60,"ATE_LoopBackTask",param_1,param_1 + 0xa78454,param_1 + 0xa78478
                );
  if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) {
    *(undefined4 *)(param_1 + 0xa77ba4) = 0;
    __init_waitqueue_head(param_1 + 0xa77ba8,"&x->wait",&g_EBF_certification);
  }
  *(undefined4 *)(param_1 + 0xa77b90) = 0;
  __init_waitqueue_head(param_1 + 0xa77b94,"&x->wait",&g_EBF_certification);
  os_zero_mem(param_1 + 0xa3bafc,0x1c);
  puVar3 = (undefined4 *)(param_1 + 0xa3abcc);
  *(undefined1 *)(param_1 + 0xa3baf8) = 0;
  *(undefined1 *)(param_1 + 0xa3baf9) = 0;
  *(undefined1 *)(param_1 + 0xa3bafa) = 0;
  *(undefined1 *)(param_1 + 0xa77ba0) = 0;
  *(undefined4 *)(param_1 + 0xa77b58) = 0;
  *(undefined1 *)(param_1 + 0xa3a010) = 0;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  } while (puVar3 != (undefined4 *)(param_1 + 0xa3ac0c));
  os_zero_mem(param_1 + 0xa3a000,0xd);
  *(undefined1 *)(param_1 + 0xa3a00b) = 1;
  *(undefined1 *)(param_1 + 0xa3a00c) = 1;
  return iVar1;
}

