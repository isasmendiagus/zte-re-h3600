// module: tm.ko
// function: getPort @ 0x4f108
// size: 188 bytes
//

undefined4 getPort(undefined4 param_1,undefined4 *param_2)

{
  switch(param_1) {
  case 0:
    *param_2 = 1;
    param_2[1] = 1;
    return 0;
  case 1:
    *param_2 = 2;
    param_2[1] = 2;
    return 0;
  case 2:
    *param_2 = 3;
    param_2[1] = 3;
    return 0;
  case 3:
    *param_2 = 4;
    param_2[1] = 4;
    return 0;
  case 4:
    *param_2 = 5;
    param_2[1] = 5;
    return 0;
  case 5:
    *param_2 = 0;
    param_2[1] = 0;
    return 0;
  case 6:
    *param_2 = 6;
    param_2[1] = 6;
    return 0;
  case 7:
    *param_2 = 7;
    param_2[1] = 7;
    return 0;
  default:
    *param_2 = 8;
    param_2[1] = 8;
    return 0xffffffff;
  }
}

