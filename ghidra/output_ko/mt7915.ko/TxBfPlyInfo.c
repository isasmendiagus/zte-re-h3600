// module: mt7915.ko
// function: TxBfPlyInfo @ 0x870f8
// size: 20 bytes
//

bool TxBfPlyInfo(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfPlyInfo();
  return iVar1 == 0;
}

