// module: mt7915.ko
// function: RcGetRadioCurStat @ 0xac850
// size: 12 bytes
//

undefined1 RcGetRadioCurStat(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 4) + 1);
}

