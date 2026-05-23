// module: mt7915.ko
// function: TxBfProfileTag_DesiredNr @ 0x8692c
// size: 8 bytes
//

void TxBfProfileTag_DesiredNr(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x2c) = param_2;
  return;
}

