// module: mt7915.ko
// function: PrintSrEventSrCnt @ 0x1713b4
// size: 48 bytes
//

void PrintSrEventSrCnt(int param_1)

{
  if (-1 < DebugLevel) {
    FUN_0016b708();
  }
  PrintSrCnt(*(undefined1 *)(param_1 + 2),param_1 + 0xc);
  return;
}

