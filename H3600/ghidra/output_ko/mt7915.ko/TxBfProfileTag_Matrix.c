// module: mt7915.ko
// function: TxBfProfileTag_Matrix @ 0x868bc
// size: 36 bytes
//

void TxBfProfileTag_Matrix
               (int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
               undefined1 param_5,undefined1 param_6)

{
  *(undefined1 *)(param_1 + 6) = param_2;
  *(undefined1 *)(param_1 + 7) = param_3;
  *(undefined1 *)(param_1 + 9) = param_4;
  *(undefined1 *)(param_1 + 4) = param_5;
  *(undefined1 *)(param_1 + 8) = param_6;
  return;
}

