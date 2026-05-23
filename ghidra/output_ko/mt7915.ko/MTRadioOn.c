// module: mt7915.ko
// function: MTRadioOn @ 0x19a170
// size: 208 bytes
//

void MTRadioOn(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar3 == 0x7622 || uVar3 == 0x7915) {
    iVar2 = IsHcAllSupportedBandsRadioOff();
    if (iVar2 != 0) {
      DriverOwn(param_1);
    }
    uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  }
  if (uVar3 == 0x7603) {
    MtCmdRadioOnOffCtrl(param_1,1);
  }
  else {
    uVar1 = HcGetBandByChannel(param_1,*(undefined1 *)(param_2 + 0x1a));
    RTMP_RADIO_ON_OFF_CTRL(param_1,uVar1,1);
  }
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7603) {
    AsicSetMacTxRx(param_1,2,1);
  }
  HcSetRadioCurStatByChannel(param_1,*(undefined1 *)(param_2 + 0x1a),1);
  return;
}

