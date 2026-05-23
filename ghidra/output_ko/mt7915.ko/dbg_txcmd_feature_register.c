// module: mt7915.ko
// function: dbg_txcmd_feature_register @ 0x28dfdc
// size: 32 bytes
//

undefined4 dbg_txcmd_feature_register(int *param_1,int *param_2)

{
  *param_2 = *param_1;
  param_2[1] = (int)param_1;
  *(int **)(*param_1 + 4) = param_2;
  *param_1 = (int)param_2;
  return 0;
}

