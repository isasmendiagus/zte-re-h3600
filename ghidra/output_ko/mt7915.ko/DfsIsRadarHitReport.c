// module: mt7915.ko
// function: DfsIsRadarHitReport @ 0x234738
// size: 28 bytes
//

bool DfsIsRadarHitReport(int param_1)

{
  return *(char *)(param_1 + 0x795408) == '\x01';
}

