// module: mt7915.ko
// function: TpcDlAlgoCtrl @ 0xed5d8
// size: 48 bytes
//

bool TpcDlAlgoCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdTpcDlAlgoCtrl();
  return iVar1 == 0;
}

