// module: mt7915.ko
// function: PrintSrEventSrSd @ 0x1713e4
// size: 48 bytes
//

void PrintSrEventSrSd(int param_1)

{
  if (-1 < DebugLevel) {
    FUN_0016b708();
  }
  PrintSrSd(*(undefined1 *)(param_1 + 2),param_1 + 0xc);
  return;
}

