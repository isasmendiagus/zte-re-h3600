// module: mt7915.ko
// function: MlmeResetRalinkCounters @ 0x129b9c
// size: 36 bytes
//

void MlmeResetRalinkCounters(int param_1)

{
  *(undefined4 *)(param_1 + 0xa39e84) = *(undefined4 *)(param_1 + 0xa39e28);
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return;
  }
  FUN_001288b4();
  return;
}

