// module: mt7915.ko
// function: RTMPEnableRxTx @ 0x13c918
// size: 132 bytes
//

void RTMPEnableRxTx(int param_1)

{
  undefined4 uVar1;
  
  if (2 < DebugLevel) {
    printk("==> RTMPEnableRxTx\n");
  }
  hif_dma_enable(*(undefined4 *)(param_1 + 0xa797a0));
  AsicSetRxFilter(param_1);
  if (*(char *)(param_1 + 0x795b0d) == '\0') {
    uVar1 = 3;
  }
  else {
    uVar1 = 4;
  }
  AsicSetMacTxRx(param_1,uVar1,1);
  if (2 < DebugLevel) {
    printk("<== RTMPEnableRxTx\n");
    return;
  }
  return;
}

