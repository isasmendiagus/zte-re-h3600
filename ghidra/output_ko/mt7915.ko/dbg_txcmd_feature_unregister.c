// module: mt7915.ko
// function: dbg_txcmd_feature_unregister @ 0x28dffc
// size: 48 bytes
//

void dbg_txcmd_feature_unregister(int *param_1)

{
  if (*param_1 != 0) {
    *(int *)(*param_1 + 4) = param_1[1];
  }
  if ((int *)param_1[1] != (int *)0x0) {
    *(int *)param_1[1] = *param_1;
  }
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

