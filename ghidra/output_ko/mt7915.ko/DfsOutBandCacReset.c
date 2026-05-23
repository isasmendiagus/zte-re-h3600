// module: mt7915.ko
// function: DfsOutBandCacReset @ 0x2347f0
// size: 28 bytes
//

void DfsOutBandCacReset(int param_1)

{
  *(undefined2 *)(param_1 + 0x795400) = 0;
  *(undefined1 *)(param_1 + 0x795402) = 0;
  return;
}

