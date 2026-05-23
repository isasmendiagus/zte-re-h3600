// module: mt7915.ko
// function: TxBfProfilePnRead @ 0x86dbc
// size: 20 bytes
//

bool TxBfProfilePnRead(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfPfmuProfilePnRead();
  return iVar1 == 0;
}

