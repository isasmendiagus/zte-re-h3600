// module: mt7915.ko
// function: TxBfQdRead @ 0x870bc
// size: 20 bytes
//

bool TxBfQdRead(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfQdRead();
  return iVar1 == 0;
}

