// module: mt7915.ko
// function: RcSetRadioCurStat @ 0xac85c
// size: 12 bytes
//

void RcSetRadioCurStat(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 4) + 1) = param_2;
  return;
}

