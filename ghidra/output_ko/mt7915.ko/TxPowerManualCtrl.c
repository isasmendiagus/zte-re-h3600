// module: mt7915.ko
// function: TxPowerManualCtrl @ 0xed644
// size: 44 bytes
//

bool TxPowerManualCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdSetForceTxPowerCtrl();
  return iVar1 == 0;
}

