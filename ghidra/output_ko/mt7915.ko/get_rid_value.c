// module: mt7915.ko
// function: get_rid_value @ 0x17f3e4
// size: 24 bytes
//

uint get_rid_value(int param_1)

{
  DataSynchronizationBarrier(0xf);
  return *(uint *)(*(int *)(param_1 + 0xbc) + 0xd7090) & 0x7fffffff;
}

