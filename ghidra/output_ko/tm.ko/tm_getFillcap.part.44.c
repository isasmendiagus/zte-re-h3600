// module: tm.ko
// function: tm_getFillcap.part.44 @ 0x4d598
// size: 52 bytes
//

uint tm_getFillcap_part_44(uint param_1)

{
  param_1 = param_1 >> 8;
  if (199999 < param_1) {
    if (0x1ffffe < param_1) {
      param_1 = 0x1fffff;
    }
    return param_1;
  }
  return 200000;
}

