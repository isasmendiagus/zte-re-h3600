// module: mt7915.ko
// function: TxPowerPercentCtrl @ 0xed670
// size: 20 bytes
//

bool TxPowerPercentCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdTxPowerPercentCtrl();
  return iVar1 == 0;
}

