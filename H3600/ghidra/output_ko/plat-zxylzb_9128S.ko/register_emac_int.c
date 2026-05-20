// module: plat-zxylzb_9128S.ko
// function: register_emac_int @ 0x1b1bc
// size: 24 bytes
//

void register_emac_int(undefined4 param_1,undefined4 param_2)

{
  pon_int_info._0_4_ = param_2;
  epon_isr = param_1;
  pon_int_enable(0x100);
  return;
}

