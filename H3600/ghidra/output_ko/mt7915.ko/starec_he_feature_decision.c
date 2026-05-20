// module: mt7915.ko
// function: starec_he_feature_decision @ 0x205c00
// size: 48 bytes
//

undefined4 starec_he_feature_decision(int param_1,int param_2,uint *param_3)

{
  uint uVar1;
  
  if ((*(uint *)(param_2 + 100) & 0x18) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x4000;
  }
  if (*(int *)(param_1 + 0x14) == 2) {
    uVar1 = uVar1 | 0x80000;
  }
  *param_3 = *param_3 | uVar1;
  return 1;
}

