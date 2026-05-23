// module: mt7915.ko
// function: NICInitAsicFromEEPROM @ 0x13cd2c
// size: 336 bytes
//

void NICInitAsicFromEEPROM(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (2 < DebugLevel) {
    printk("--> NICInitAsicFromEEPROM\n");
  }
  uVar1 = *(undefined2 *)("rtmp_read_vow_parms_from_file" + param_1 + 6);
  AntCfgInit(param_1);
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x7c) != (code *)0x0) {
    (**(code **)(iVar2 + 0x7c))(param_1);
  }
  InitRFRegisters(param_1);
  RTMPCfgTssiGainFromEEPROM(param_1);
  if (*(char *)(param_1 + 0x286285) == '\0') {
    uVar3 = HcGetBandByWdev(&DAT_0036db58 + param_1);
    RTMPStaCfgRadioCtrlFromEEPROM(param_1,uVar1);
    AsicSetTxStream(param_1,(byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4,0,0,uVar3);
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x78) != (code *)0x0) {
    (**(code **)(iVar2 + 0x78))(param_1);
  }
  AsicBbpInitFromEEPROM(param_1);
  if (2 < DebugLevel) {
    printk("TxPath = %d, RxPath = %d, RFIC=%d\n",
           (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4,
           "SetPartProfileParameters"[param_1 + 0x18] & 0xf,
           "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e]);
    if (2 < DebugLevel) {
      printk("<-- NICInitAsicFromEEPROM\n");
      return;
    }
  }
  return;
}

