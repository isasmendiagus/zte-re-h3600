// module: mt7915.ko
// function: WtcExit @ 0xad988
// size: 16 bytes
//

void WtcExit(int param_1)

{
  os_zero_mem(param_1 + 0x1a28,0x120c);
  return;
}

