// module: mt7915.ko
// function: TxBfProfileDataRead @ 0x86f78
// size: 20 bytes
//

bool TxBfProfileDataRead(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfPfmuProfileDataRead();
  return iVar1 == 0;
}

