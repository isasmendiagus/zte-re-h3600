// module: plat-zxylzb_9128S.ko
// function: get_mac_status @ 0x162d0
// size: 76 bytes
//

char * get_mac_status(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  param_1 = param_1 & 0xf;
  if (param_1 == 0) {
    return "invalid";
  }
  if (param_1 != 0xf) {
    sprintf(&buf_name_18119,"valid %d",param_1,param_4,param_4);
    return &buf_name_18119;
  }
  return "static";
}

