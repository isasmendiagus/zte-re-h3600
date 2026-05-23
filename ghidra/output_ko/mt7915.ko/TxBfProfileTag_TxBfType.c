// module: mt7915.ko
// function: TxBfProfileTag_TxBfType @ 0x86858
// size: 8 bytes
//

void TxBfProfileTag_TxBfType(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 2) = param_2;
  return;
}

