// module: mt7915.ko
// function: mt_op_dbdc_continuous_tx @ 0x258034
// size: 120 bytes
//

undefined4 mt_op_dbdc_continuous_tx(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = MtCmdTxContinous(iVar1,*(undefined1 *)(param_3 + 0xc55),*(undefined1 *)(param_3 + 0xc56)
                             ,*(undefined1 *)(param_3 + 0xc53),*(undefined1 *)(param_3 + 0xc50),
                             *(undefined4 *)(param_3 + 0xcc8),*(undefined4 *)(param_3 + 0xcc4),
                             *(undefined4 *)(param_3 + 0xccc),param_2,
                             *(undefined1 *)(param_3 + 0xca4));
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

