// module: mt7915.ko
// function: build_ext_channel_switch_ie @ 0x1469e4
// size: 112 bytes
//

void build_ext_channel_switch_ie
               (undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4,
               int param_5)

{
  undefined1 uVar1;
  char *pcVar2;
  
  if (param_5 == 0) {
    return;
  }
  pcVar2 = *(char **)(param_5 + 0x3fe4);
  if (pcVar2 == (char *)0x0) {
    return;
  }
  param_2[1] = 4;
  *param_2 = 0x3c;
  param_2[2] = 1;
  uVar1 = get_regulatory_class(param_1,param_3,param_4,param_5);
  param_2[4] = (char)param_3;
  param_2[3] = uVar1;
  param_2[5] = (pcVar2[1] + -1) - *pcVar2;
  return;
}

