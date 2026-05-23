// module: mt7915.ko
// function: MlmeValidateSSID @ 0x129bc0
// size: 76 bytes
//

undefined4 MlmeValidateSSID(byte *param_1,uint param_2)

{
  byte *pbVar1;
  
  if (param_2 < 0x21) {
    if (param_2 == 0) {
      return 1;
    }
    if (0x1f < *param_1) {
      pbVar1 = param_1 + param_2;
      do {
        param_1 = param_1 + 1;
        if (param_1 == pbVar1) {
          return 1;
        }
      } while (0x1f < *param_1);
    }
  }
  return 0;
}

