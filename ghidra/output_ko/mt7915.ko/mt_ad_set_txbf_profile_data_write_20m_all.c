// module: mt7915.ko
// function: mt_ad_set_txbf_profile_data_write_20m_all @ 0x25d56c
// size: 88 bytes
//

undefined4
mt_ad_set_txbf_profile_data_write_20m_all(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_210 [512];
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  iVar2 = TxBfProfileDataFormatTranslate(uVar1,param_3,auStack_210);
  if (iVar2 == 0) {
    uVar3 = 0x100;
  }
  else {
    uVar3 = 0;
  }
  iVar2 = CmdETxBfPfmuProfileDataWrite20MAll(uVar1,param_2,auStack_210);
  if (iVar2 != 0) {
    uVar3 = 0x100;
  }
  return uVar3;
}

