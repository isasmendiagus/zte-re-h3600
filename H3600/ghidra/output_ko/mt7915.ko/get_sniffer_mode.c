// module: mt7915.ko
// function: get_sniffer_mode @ 0x2440d0
// size: 8 bytes
//

undefined1 get_sniffer_mode(int param_1)

{
  return *(undefined1 *)(param_1 + 0x4cc);
}

