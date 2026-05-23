// module: mt7915.ko
// function: TxPowerRfTxAnt @ 0xed7c8
// size: 20 bytes
//

bool TxPowerRfTxAnt(void)

{
  int iVar1;
  
  iVar1 = MtCmdTxPwrRfTxAntCtrl();
  return iVar1 == 0;
}

