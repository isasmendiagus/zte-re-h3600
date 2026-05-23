// module: mt7915.ko
// function: set_sniffer_mode @ 0x2440d8
// size: 8 bytes
//

void set_sniffer_mode(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x4cc) = param_2;
  return;
}

