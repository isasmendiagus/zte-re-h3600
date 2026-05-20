// module: mt7915.ko
// function: RcGetPhyMode @ 0xac820
// size: 12 bytes
//

undefined2 RcGetPhyMode(int param_1)

{
  return *(undefined2 *)(*(int *)(param_1 + 4) + 2);
}

