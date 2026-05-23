// module: plat-zxylzb_9128S.ko
// function: register_gmac_int @ 0x1b784
// size: 24 bytes
//

void register_gmac_int(undefined4 param_1,undefined4 param_2)

{
  gpon_isr = param_1;
  pon_int_info._0_4_ = param_2;
  pon_int_enable(1);
  return;
}

