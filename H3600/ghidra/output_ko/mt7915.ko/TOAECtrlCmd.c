// module: mt7915.ko
// function: TOAECtrlCmd @ 0xed7f0
// size: 20 bytes
//

bool TOAECtrlCmd(void)

{
  int iVar1;
  
  iVar1 = MtCmdTOAECalCtrl();
  return iVar1 == 0;
}

