// module: mt7915.ko
// function: APAsicRxAntEvalTimeout @ 0x17ac4
// size: 132 bytes
//

void APAsicRxAntEvalTimeout(int param_1)

{
  if (((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) &&
     ((*(int *)(param_1 + 0xa77bb4) != 1 ||
      ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))) {
    bbp_set_rxpath(param_1,*(undefined1 *)(param_1 + 0x829220));
    return;
  }
  return;
}

