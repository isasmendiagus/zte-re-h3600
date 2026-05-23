// module: mt7915.ko
// function: DfsIsTargetChAvailable @ 0x234768
// size: 36 bytes
//

bool DfsIsTargetChAvailable(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (*(char *)(param_1 + 0x7953f1) != '\0') {
    bVar1 = *(short *)(param_1 + 0x7953f4) == 0;
  }
  return bVar1;
}

