// module: mt7915.ko
// function: TxBfProfileTag_SNR @ 0x868e0
// size: 24 bytes
//

void TxBfProfileTag_SNR(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                       undefined1 param_5)

{
  *(undefined1 *)(param_1 + 0x1c) = param_2;
  *(undefined1 *)(param_1 + 0x1d) = param_3;
  *(undefined1 *)(param_1 + 0x1e) = param_4;
  *(undefined1 *)(param_1 + 0x1f) = param_5;
  return;
}

