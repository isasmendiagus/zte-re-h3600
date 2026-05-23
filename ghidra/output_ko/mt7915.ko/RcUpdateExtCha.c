// module: mt7915.ko
// function: RcUpdateExtCha @ 0xac804
// size: 16 bytes
//

undefined4 RcUpdateExtCha(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 4) + 8) = param_2;
  return 0xffffffff;
}

