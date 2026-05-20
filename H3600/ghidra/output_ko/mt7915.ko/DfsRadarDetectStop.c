// module: mt7915.ko
// function: DfsRadarDetectStop @ 0x235d40
// size: 28 bytes
//

void DfsRadarDetectStop(undefined4 param_1,int param_2)

{
  *(undefined1 *)(param_2 + 0x2b7) = 0;
  *(undefined1 *)(param_2 + 0x2b8) = 0;
  if (*(char *)(param_2 + 0x2bf) == '\0') {
    return;
  }
  mtRddControl(param_1,0,0,0,0);
  mtRddControl(param_1,0,1,0,0);
  return;
}

