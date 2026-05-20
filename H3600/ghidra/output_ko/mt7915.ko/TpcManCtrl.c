// module: mt7915.ko
// function: TpcManCtrl @ 0xed534
// size: 20 bytes
//

bool TpcManCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdTpcManCtrl();
  return iVar1 == 0;
}

