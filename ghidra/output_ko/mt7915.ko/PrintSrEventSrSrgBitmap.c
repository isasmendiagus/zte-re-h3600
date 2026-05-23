// module: mt7915.ko
// function: PrintSrEventSrSrgBitmap @ 0x171414
// size: 48 bytes
//

void PrintSrEventSrSrgBitmap(int param_1)

{
  if (-1 < DebugLevel) {
    FUN_0016b708();
  }
  PrintSrSrgBitmap(*(undefined1 *)(param_1 + 2),param_1 + 0xc);
  return;
}

