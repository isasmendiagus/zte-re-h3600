// module: mt7915.ko
// function: mt_op_dbdc_tx_tone_pwr @ 0x257fe4
// size: 80 bytes
//

undefined4 mt_op_dbdc_tx_tone_pwr(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = MtCmdTxTonePower(iVar1,0x12,*(undefined4 *)(param_3 + 0xcc0),
                             *(undefined1 *)(param_3 + 0xca8),param_2);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

