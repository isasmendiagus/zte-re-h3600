// module: mt7915.ko
// function: TxBfProfileTag_DesiredNc @ 0x86924
// size: 8 bytes
//

void TxBfProfileTag_DesiredNc(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x2d) = param_2;
  return;
}

