// module: mt7915.ko
// function: raStbcSettingCheck @ 0x1d9180
// size: 72 bytes
//

undefined4
raStbcSettingCheck(undefined4 param_1,undefined4 param_2,uint param_3,int param_4,char param_5,
                  char param_6)

{
  if (param_5 != '\x01' && param_6 != '\x01') {
    switch(param_2) {
    case 2:
    case 3:
      if (7 < param_3) {
        param_1 = 0;
      }
      return param_1;
    case 4:
    case 8:
      if (param_4 != 1) {
        param_1 = 0;
      }
      return param_1;
    }
  }
  return 0;
}

