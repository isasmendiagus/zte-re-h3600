// module: mt7915.ko
// function: TxBfTxSndInfo @ 0x870e4
// size: 20 bytes
//

bool TxBfTxSndInfo(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfTxSndInfo();
  return iVar1 == 0;
}

