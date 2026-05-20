// module: mt7915.ko
// function: MuPwrCtrlCmd @ 0xed804
// size: 20 bytes
//

bool MuPwrCtrlCmd(void)

{
  int iVar1;
  
  iVar1 = MtCmdMuPwrCtrl();
  return iVar1 == 0;
}

