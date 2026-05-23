// module: mt7915.ko
// function: TxBfTxCmd @ 0x8710c
// size: 20 bytes
//

bool TxBfTxCmd(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfTxCmd();
  return iVar1 == 0;
}

