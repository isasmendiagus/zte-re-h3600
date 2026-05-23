// module: mt7915.ko
// function: HcGetRadioPhyMode @ 0xa9948
// size: 24 bytes
//

undefined2 HcGetRadioPhyMode(int param_1)

{
  return *(undefined2 *)(*(int *)(param_1 + 0xa797a0) + 0x169e);
}

