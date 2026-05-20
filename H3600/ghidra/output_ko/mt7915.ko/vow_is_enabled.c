// module: mt7915.ko
// function: vow_is_enabled @ 0x42438
// size: 32 bytes
//

bool vow_is_enabled(int param_1)

{
  return (*(uint *)(param_1 + 0xa7a2e8) & 0xff00ff) != 0;
}

