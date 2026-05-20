// module: plat-zxylzb_9128S.ko
// function: pon_pp_ctrl_init @ 0x17c70
// size: 72 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 pon_pp_ctrl_init(void)

{
  pp_base[10] = 0x1070104;
  *pp_base = 2;
  (*_request_threaded_irq)(0x66665b0);
  return 0;
}

