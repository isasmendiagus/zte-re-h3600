// module: mt7915.ko
// function: TxBfProfileTag_SeIdx @ 0x86900
// size: 8 bytes
//

void TxBfProfileTag_SeIdx(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x28) = param_2;
  return;
}

