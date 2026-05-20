// module: mt7915.ko
// function: HcGetAutoChCtrlbyBandIdx @ 0xa9b18
// size: 32 bytes
//

int HcGetAutoChCtrlbyBandIdx(int param_1,int param_2)

{
  return param_2 * 0x354 + *(int *)(param_1 + 0xa797a0) + 0x1364;
}

