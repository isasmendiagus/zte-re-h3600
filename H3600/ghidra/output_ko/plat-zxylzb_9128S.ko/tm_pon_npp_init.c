// module: plat-zxylzb_9128S.ko
// function: tm_pon_npp_init @ 0x1318c
// size: 208 bytes
//

undefined4 tm_pon_npp_init(void)

{
  printk("pon_npp init\n");
  *(undefined4 *)(npp_base + 8) = 0xffffff;
  *(undefined4 *)(npp_base + 0xc) = 0xfffff;
  msleep(1);
  pon_npp_idm_init();
  pon_npp_spa_init();
  pon_npp_sipc_init();
  pon_npp_smct_init();
  *(undefined4 *)(npp_base + 4) = 0xffffffff;
  *(undefined4 *)(npp_base + 0x48) = 0;
  pon_npp_smac_init();
  request_threaded_irq(g_npp_irq,pon_npp_int,0,0,"pon_npp",0);
  *(uint *)(npp_base + 0x40) = *(uint *)(npp_base + 0x40) | 0x300;
  *(undefined4 *)(npp_base + 0x10008) = 0x80;
  pon_npp_uopc_init();
  return 0;
}

