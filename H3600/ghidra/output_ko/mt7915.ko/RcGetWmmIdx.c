// module: mt7915.ko
// function: RcGetWmmIdx @ 0xabeb8
// size: 48 bytes
//

undefined1 RcGetWmmIdx(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  if ((*(int *)(param_1 + 8) != 0) && (*(int *)(*(int *)(param_1 + 8) + 4) != 0)) {
    return *(undefined1 *)(param_1 + 5);
  }
  return 0;
}

