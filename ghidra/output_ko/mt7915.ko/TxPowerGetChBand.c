// module: mt7915.ko
// function: TxPowerGetChBand @ 0xed8d8
// size: 24 bytes
//

byte TxPowerGetChBand(int param_1,uint param_2)

{
  bool bVar1;
  
  bVar1 = param_2 == 0xd;
  if (param_2 < 0xe) {
    bVar1 = param_1 == 0;
  }
  return bVar1 ^ 1;
}

