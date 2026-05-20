// module: mt7915.ko
// function: bssinfo_sta_feature_decision @ 0x687cc
// size: 24 bytes
//

undefined4 bssinfo_sta_feature_decision(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  *param_3 = *param_3 | 0x10018;
  return 1;
}

