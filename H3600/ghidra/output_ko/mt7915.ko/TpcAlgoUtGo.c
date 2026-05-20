// module: mt7915.ko
// function: TpcAlgoUtGo @ 0xed5c4
// size: 20 bytes
//

bool TpcAlgoUtGo(void)

{
  int iVar1;
  
  iVar1 = MtCmdTpcUlUtGo();
  return iVar1 == 0;
}

