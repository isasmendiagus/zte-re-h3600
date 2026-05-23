// module: mt7915.ko
// function: TpcUlAlgoCtrl @ 0xed580
// size: 48 bytes
//

bool TpcUlAlgoCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdTpcUlAlgoCtrl();
  return iVar1 == 0;
}

