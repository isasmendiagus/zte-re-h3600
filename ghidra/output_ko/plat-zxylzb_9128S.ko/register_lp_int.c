// module: plat-zxylzb_9128S.ko
// function: register_lp_int @ 0x1b1d4
// size: 24 bytes
//

void register_lp_int(undefined4 param_1,undefined4 param_2)

{
  lp_isr = param_1;
  pon_int_info._0_4_ = param_2;
  pon_int_enable(0x40);
  return;
}

