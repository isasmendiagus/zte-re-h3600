// module: mt7915.ko
// function: mt_op_dbdc_tx_tone @ 0x257f70
// size: 116 bytes
//

undefined4 mt_op_dbdc_tx_tone(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = MtCmdTxTone(iVar1,param_2,*(undefined1 *)(param_3 + 0xca4),
                        *(undefined1 *)(param_3 + 0xca8),*(undefined1 *)(param_3 + 0xcac),
                        *(undefined1 *)(param_3 + 0xcb0),*(undefined4 *)(param_3 + 0xcb4),
                        *(undefined4 *)(param_3 + 0xcb8),*(undefined1 *)(param_3 + 0xc51));
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

