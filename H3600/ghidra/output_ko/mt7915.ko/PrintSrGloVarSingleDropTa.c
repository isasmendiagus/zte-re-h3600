// module: mt7915.ko
// function: PrintSrGloVarSingleDropTa @ 0x16d2f8
// size: 80 bytes
//

void PrintSrGloVarSingleDropTa(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (-1 < DebugLevel) {
    printk("SR Info - u1CurSrDropTaIdx = %d, u2SrTtlTxCntThr=%d\n",*(undefined1 *)(param_1 + 1),
           *(undefined2 *)(param_1 + 2));
  }
  PrintSrDropTaInfo(param_1 + 4,param_2,param_3);
  return;
}

