// module: mt7915.ko
// function: TpcWlanIdCtrl @ 0xed55c
// size: 36 bytes
//

bool TpcWlanIdCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdTpcWlanIdCtrl();
  return iVar1 == 0;
}

