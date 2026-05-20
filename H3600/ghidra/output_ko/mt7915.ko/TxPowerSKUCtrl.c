// module: mt7915.ko
// function: TxPowerSKUCtrl @ 0xed61c
// size: 20 bytes
//

bool TxPowerSKUCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdTxPowerSKUCtrl();
  return iVar1 == 0;
}

