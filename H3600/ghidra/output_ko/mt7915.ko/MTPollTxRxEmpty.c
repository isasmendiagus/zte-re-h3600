// module: mt7915.ko
// function: MTPollTxRxEmpty @ 0x19a0bc
// size: 16 bytes
//

void MTPollTxRxEmpty(int param_1)

{
  hif_poll_txrx_empty(*(undefined4 *)(param_1 + 0xa797a0));
  return;
}

