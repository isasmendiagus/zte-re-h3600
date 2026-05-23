// module: mt7915.ko
// function: cal_ht_cent_ch @ 0x137bd0
// size: 120 bytes
//

undefined4 cal_ht_cent_ch(uint param_1,int param_2,int param_3,char *param_4)

{
  undefined4 uVar1;
  
  if (param_3 == 1 && param_2 == 1) {
    *param_4 = (char)param_1 + '\x02';
    return 1;
  }
  uVar1 = 0;
  if (2 < param_1 && (param_3 == 3 && param_2 == 1)) {
    if (param_1 == 0xe) {
      *param_4 = '\r';
      return 1;
    }
    uVar1 = 1;
    param_1 = param_1 - 2;
  }
  *param_4 = (char)param_1;
  return uVar1;
}

