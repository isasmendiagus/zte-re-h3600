// module: mt7915.ko
// function: TxBfProfileTag_InValid @ 0x86870
// size: 8 bytes
//

void TxBfProfileTag_InValid(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 10) = param_2;
  return;
}

