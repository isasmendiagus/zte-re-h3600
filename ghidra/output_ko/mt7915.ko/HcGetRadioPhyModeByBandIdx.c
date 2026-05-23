// module: mt7915.ko
// function: HcGetRadioPhyModeByBandIdx @ 0xa9960
// size: 32 bytes
//

undefined2 HcGetRadioPhyModeByBandIdx(int param_1,int param_2)

{
  return *(undefined2 *)(param_2 * 0x354 + *(int *)(param_1 + 0xa797a0) + 0x169e);
}

