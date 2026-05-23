// module: mt7915.ko
// function: TpcManTblInfo @ 0xed608
// size: 20 bytes
//

bool TpcManTblInfo(void)

{
  int iVar1;
  
  iVar1 = MtCmdTpcManTblInfo();
  return iVar1 == 0;
}

