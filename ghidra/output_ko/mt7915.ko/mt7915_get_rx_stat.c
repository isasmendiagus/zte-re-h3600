// module: mt7915.ko
// function: mt7915_get_rx_stat @ 0x17bc64
// size: 20 bytes
//

bool mt7915_get_rx_stat(void)

{
  int iVar1;
  
  iVar1 = mt_cmd_get_rx_stat();
  return iVar1 != 0;
}

