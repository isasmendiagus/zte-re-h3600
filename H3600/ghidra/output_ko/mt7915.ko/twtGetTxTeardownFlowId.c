// module: mt7915.ko
// function: twtGetTxTeardownFlowId @ 0x16a638
// size: 12 bytes
//

byte twtGetTxTeardownFlowId(int param_1)

{
  return *(byte *)(param_1 + 0x1a) & 7;
}

