// module: mt7915.ko
// function: media_state_connected @ 0x17050
// size: 44 bytes
//

bool media_state_connected(int param_1)

{
  return (*(uint *)(*(int *)(param_1 + 8) + 0x795124) & 0x200080) == 0x200080;
}

