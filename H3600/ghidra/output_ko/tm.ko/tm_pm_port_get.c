// module: tm.ko
// function: tm_pm_port_get @ 0x54fa4
// size: 152 bytes
//

undefined4 tm_pm_port_get(undefined4 param_1,undefined4 *param_2)

{
  switch(param_1) {
  case 0:
    *param_2 = 1;
    return 0;
  case 1:
    *param_2 = 2;
    return 0;
  case 2:
    *param_2 = 3;
    return 0;
  case 3:
    *param_2 = 4;
    return 0;
  case 4:
    *param_2 = 5;
    return 0;
  case 5:
    *param_2 = 0;
    return 0;
  case 6:
    *param_2 = 6;
    return 0;
  case 7:
    *param_2 = 7;
    return 0;
  default:
    *param_2 = 8;
    return 0xffffffff;
  }
}

