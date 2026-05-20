// module: tm.ko
// function: tm_port_name_get @ 0x512e4
// size: 192 bytes
//

undefined4 tm_port_name_get(undefined4 param_1,undefined4 *param_2)

{
  switch(param_1) {
  case 0:
    *param_2 = &_LC383;
    return 0;
  case 1:
    *param_2 = &_LC384;
    return 0;
  case 2:
    *param_2 = &_LC385;
    return 0;
  case 3:
    *param_2 = &_LC386;
    return 0;
  case 4:
    *param_2 = &_LC387;
    return 0;
  case 5:
    *param_2 = &_LC382;
    return 0;
  case 6:
    *param_2 = "wifi0";
    return 0;
  case 7:
    *param_2 = "wifi1";
    return 0;
  default:
    *param_2 = "error";
    return 0xffffffff;
  }
}

