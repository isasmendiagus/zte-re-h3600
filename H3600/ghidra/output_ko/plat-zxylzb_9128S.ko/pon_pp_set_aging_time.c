// module: plat-zxylzb_9128S.ko
// function: pon_pp_set_aging_time @ 0x178b8
// size: 40 bytes
//

void pon_pp_set_aging_time(int param_1)

{
  *(int *)(pp_base + 0x8188) = param_1 * 0x1107;
  return;
}

