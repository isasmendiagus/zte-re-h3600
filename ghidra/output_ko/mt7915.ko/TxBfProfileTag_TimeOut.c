// module: mt7915.ko
// function: TxBfProfileTag_TimeOut @ 0x86914
// size: 8 bytes
//

void TxBfProfileTag_TimeOut(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x2a) = param_2;
  return;
}

