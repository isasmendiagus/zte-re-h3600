// module: mt7915.ko
// function: TxBfProfileTag_DesiredBW @ 0x8691c
// size: 8 bytes
//

void TxBfProfileTag_DesiredBW(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x2b) = param_2;
  return;
}

