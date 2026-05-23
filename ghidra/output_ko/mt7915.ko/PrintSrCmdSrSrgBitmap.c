// module: mt7915.ko
// function: PrintSrCmdSrSrgBitmap @ 0x170dbc
// size: 48 bytes
//

void PrintSrCmdSrSrgBitmap(int param_1)

{
  if (0 < DebugLevel) {
    FUN_0016b3c0();
  }
  PrintSrSrgBitmap(*(undefined1 *)(param_1 + 2),param_1 + 0xc);
  return;
}

