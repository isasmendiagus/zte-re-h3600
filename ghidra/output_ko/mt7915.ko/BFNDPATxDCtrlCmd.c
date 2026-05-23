// module: mt7915.ko
// function: BFNDPATxDCtrlCmd @ 0xed818
// size: 44 bytes
//

bool BFNDPATxDCtrlCmd(void)

{
  int iVar1;
  
  iVar1 = MtCmdBFNDPATxDCtrl();
  return iVar1 == 0;
}

