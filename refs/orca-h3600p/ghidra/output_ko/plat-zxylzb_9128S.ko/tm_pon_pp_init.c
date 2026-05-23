// module: plat-zxylzb_9128S.ko
// function: tm_pon_pp_init @ 0x17c10
// size: 96 bytes
//

undefined4 tm_pon_pp_init(void)

{
  printk("pon_pp init\n");
  pon_pp_ctrl_init();
  pon_pp_brg_init();
  pon_pp_cla_init();
  request_threaded_irq(g_pp_irq,zx_pon_pp_int,0,0,"pon_pp",0);
  return 0;
}

