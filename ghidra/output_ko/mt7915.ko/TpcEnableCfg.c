// module: mt7915.ko
// function: TpcEnableCfg @ 0xed548
// size: 20 bytes
//

bool TpcEnableCfg(void)

{
  int iVar1;
  
  iVar1 = MtCmdTpcEnableCfg();
  return iVar1 == 0;
}

