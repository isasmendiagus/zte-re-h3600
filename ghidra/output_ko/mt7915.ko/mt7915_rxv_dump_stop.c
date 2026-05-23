// module: mt7915.ko
// function: mt7915_rxv_dump_stop @ 0x172c04
// size: 24 bytes
//

undefined4 mt7915_rxv_dump_stop(int param_1)

{
  *(undefined1 *)(param_1 + 0xa7c218) = 0;
  return 0;
}

