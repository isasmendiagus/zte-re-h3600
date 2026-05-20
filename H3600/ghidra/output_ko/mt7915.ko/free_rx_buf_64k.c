// module: mt7915.ko
// function: free_rx_buf_64k @ 0x1cee08
// size: 32 bytes
//

void free_rx_buf_64k(int param_1)

{
  undefined2 extraout_r1;
  
  __aeabi_idivmod(*(ushort *)(param_1 + 0x42) + 1,*(undefined2 *)(param_1 + 0x44));
  *(undefined2 *)(param_1 + 0x42) = extraout_r1;
  return;
}

