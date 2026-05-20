// module: mt7915.ko
// function: TxBfProfilePnWrite @ 0x86dd0
// size: 20 bytes
//

bool TxBfProfilePnWrite(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfPfmuProfilePnWrite();
  return iVar1 == 0;
}

