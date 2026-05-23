// module: mt7915.ko
// function: Set_TxBfPfmuMemAllocMapRead @ 0xe5d94
// size: 20 bytes
//

bool Set_TxBfPfmuMemAllocMapRead(void)

{
  int iVar1;
  
  iVar1 = CmdPfmuMemAllocMapRead();
  return iVar1 == 0;
}

