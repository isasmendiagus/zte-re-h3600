// module: mt7915.ko
// function: free_rx_buf_1k @ 0x1cedb8
// size: 32 bytes
//

void free_rx_buf_1k(int param_1)

{
  undefined2 extraout_r1;
  
  __aeabi_idivmod(*(ushort *)(param_1 + 0x22) + 1,*(undefined2 *)(param_1 + 0x24));
  *(undefined2 *)(param_1 + 0x22) = extraout_r1;
  return;
}

