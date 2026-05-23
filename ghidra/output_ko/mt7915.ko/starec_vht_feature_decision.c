// module: mt7915.ko
// function: starec_vht_feature_decision @ 0x2039e8
// size: 36 bytes
//

undefined4 starec_vht_feature_decision(undefined4 param_1,int param_2,uint *param_3)

{
  uint uVar1;
  
  if ((*(uint *)(param_2 + 0xb4) & 0x8000000) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x400;
  }
  *param_3 = *param_3 | uVar1;
  return 1;
}

