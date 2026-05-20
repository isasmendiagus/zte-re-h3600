// module: mt7915.ko
// function: MTRadioOff @ 0x19a240
// size: 360 bytes
//

void MTRadioOff(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined8 uVar5;
  
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7603) {
    AsicSetMacTxRx(param_1,2,0);
  }
  uVar2 = HcGetBandByChannel(param_1,*(undefined1 *)(param_2 + 0x1a));
  uVar3 = hif_poll_txrx_empty(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  if (2 < DebugLevel) {
    uVar1 = *(undefined1 *)(param_2 + 0x1a);
    uVar2 = HcGetBandByChannel(param_1,uVar1);
    printk("%s(wdev): ch(%d), band(%d), tx_rx_empty(%d)\n","MTRadioOff",uVar1,uVar2,uVar3);
  }
  HcSetRadioCurStatByChannel(param_1,*(undefined1 *)(param_2 + 0x1a),2);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7603) {
    MtCmdRadioOnOffCtrl(param_1,2);
  }
  else {
    uVar2 = HcGetBandByChannel(param_1,*(undefined1 *)(param_2 + 0x1a));
    RTMP_RADIO_ON_OFF_CTRL(param_1,uVar2,2);
  }
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7622 ||
      (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    uVar5 = IsHcAllSupportedBandsRadioOff(param_1);
    uVar4 = (uint)uVar5;
    if ((uVar4 & uVar3 & 0xff) != 0) {
      FwOwn(param_1,(int)((ulonglong)uVar5 >> 0x20),uVar4);
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s(): all_bands_radio_off(%d), tx_rx_empty(%d)\n","MTRadioOff",uVar4,uVar3);
      return;
    }
  }
  return;
}

