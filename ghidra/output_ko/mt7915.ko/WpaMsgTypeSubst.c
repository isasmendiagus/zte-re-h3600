// module: mt7915.ko
// function: WpaMsgTypeSubst @ 0x1188f4
// size: 96 bytes
//

undefined4 WpaMsgTypeSubst(undefined4 param_1,undefined4 *param_2)

{
  switch(param_1) {
  case 0:
    *param_2 = 0;
    return 1;
  case 1:
    *param_2 = 1;
    return 1;
  case 2:
    *param_2 = 2;
    return 1;
  case 3:
    *param_2 = 3;
    return 1;
  case 4:
    *param_2 = 4;
    return 1;
  default:
    return 0;
  }
}

