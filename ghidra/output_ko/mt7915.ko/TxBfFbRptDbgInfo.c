// module: mt7915.ko
// function: TxBfFbRptDbgInfo @ 0x870d0
// size: 20 bytes
//

bool TxBfFbRptDbgInfo(void)

{
  int iVar1;
  
  iVar1 = CmdETxBfFbRptDbgInfo();
  return iVar1 == 0;
}

