// module: mt7915.ko
// function: TpcUlUtVarCfg @ 0xed5b0
// size: 20 bytes
//

bool TpcUlUtVarCfg(void)

{
  int iVar1;
  
  iVar1 = MtCmdTpcUlUtVarCfg();
  return iVar1 == 0;
}

