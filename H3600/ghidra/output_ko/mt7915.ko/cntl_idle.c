// module: mt7915.ko
// function: cntl_idle @ 0x10d808
// size: 16 bytes
//

bool cntl_idle(int param_1)

{
  return *(int *)(param_1 + 0xca8) == 0;
}

