// module: mt7915.ko
// function: TxPowerBfBackoffCtrl @ 0xed630
// size: 20 bytes
//

bool TxPowerBfBackoffCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdTxBfBackoffCtrl();
  return iVar1 == 0;
}

