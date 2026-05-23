// module: mt7915.ko
// function: bssinfo_he_feature_decision @ 0x205e28
// size: 52 bytes
//

undefined4 bssinfo_he_feature_decision(int param_1,uint *param_2)

{
  uint uVar1;
  
  if ((*(ushort *)(param_1 + 0x18) & 0x1c0) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x2000;
  }
  if (*(int *)(param_1 + 0x14) == 1 || *(int *)(param_1 + 0x14) == 0x4000) {
    uVar1 = uVar1 | 0x1000;
  }
  *param_2 = *param_2 | uVar1;
  return 1;
}

