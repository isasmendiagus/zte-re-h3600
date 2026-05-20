// module: tm.ko
// function: pm_port_name_get @ 0x6d3ec
// size: 192 bytes
//

undefined4 pm_port_name_get(undefined4 param_1,undefined4 *param_2)

{
  switch(param_1) {
  case 0:
    *param_2 = &_LC0;
    return 0;
  case 1:
    *param_2 = &_LC1;
    return 0;
  case 2:
    *param_2 = &_LC2;
    return 0;
  case 3:
    *param_2 = &_LC3;
    return 0;
  case 4:
    *param_2 = &_LC4;
    return 0;
  case 5:
    *param_2 = &_LC5;
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

