// module: mt7915.ko
// function: TxBfProfileTag_DBW @ 0x86860
// size: 8 bytes
//

void TxBfProfileTag_DBW(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 3) = param_2;
  return;
}

