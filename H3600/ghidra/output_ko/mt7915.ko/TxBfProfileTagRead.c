// module: mt7915.ko
// function: TxBfProfileTagRead @ 0x86934
// size: 20 bytes
//

bool TxBfProfileTagRead(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfPfmuProfileTagRead();
  return iVar1 == 0;
}

