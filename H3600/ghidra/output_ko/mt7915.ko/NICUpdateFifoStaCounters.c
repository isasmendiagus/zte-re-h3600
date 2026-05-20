// module: mt7915.ko
// function: NICUpdateFifoStaCounters @ 0x13a434
// size: 80 bytes
//

void NICUpdateFifoStaCounters(int param_1)

{
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return;
  }
  if (*(int *)(param_1 + 0xa77bb4) != 1) {
    hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    return;
  }
  if ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0) {
    return;
  }
  hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  return;
}

