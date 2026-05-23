// module: mt7915.ko
// function: TxPowerShowInfo @ 0xed7dc
// size: 20 bytes
//

bool TxPowerShowInfo(void)

{
  int iVar1;
  
  iVar1 = MtCmdTxPwrShowInfo();
  return iVar1 == 0;
}

