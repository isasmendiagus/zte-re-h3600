// module: mt7915.ko
// function: RcGetChannel @ 0xac82c
// size: 12 bytes
//

undefined1 RcGetChannel(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 4) + 4);
}

