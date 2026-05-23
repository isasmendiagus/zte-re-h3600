// module: mt7915.ko
// function: DfsReportCollision @ 0x237fa0
// size: 36 bytes
//

void DfsReportCollision(int param_1)

{
  if (*(char *)(param_1 + 0x7953fa) != '\x01') {
    return;
  }
  if (*(char *)(param_1 + 0x795408) != '\x01') {
    return;
  }
  FUN_00237f78();
  return;
}

