// module: mt7915.ko
// function: WrapDfsRadarDetectStop @ 0x235d5c
// size: 104 bytes
//

void WrapDfsRadarDetectStop(int param_1)

{
  *(undefined1 *)(param_1 + 0x7953e7) = 0;
  *(undefined1 *)(param_1 + 0x7953e8) = 0;
  if (*(char *)(param_1 + 0x7953ef) == '\0') {
    return;
  }
  mtRddControl(param_1,0,0,0,0);
  mtRddControl(param_1,0,1,0,0);
  return;
}

