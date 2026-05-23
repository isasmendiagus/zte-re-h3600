// module: mt7915.ko
// function: hc_get_mac_cap @ 0xaab88
// size: 8 bytes
//

undefined4 hc_get_mac_cap(int param_1)

{
  return *(undefined4 *)(param_1 + 0xb5c);
}

