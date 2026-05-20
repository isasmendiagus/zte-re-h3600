// module: plat-zxylzb_9128S.ko
// function: pon_tm_net_init @ 0x1a258
// size: 272 bytes
//

undefined4
pon_tm_net_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  pon_tm_netdev._4_4_ = pon_tm_net_register(1,&_LC21,param_3,param_4,param_4);
  if (pon_tm_netdev._4_4_ == 0) {
    printk("failed to register sw net\n");
    return 0xffffffff;
  }
  iVar1 = pon_tm_net_register(0,&_LC3);
  pon_tm_netdev._0_4_ = iVar1;
  if (iVar1 != 0) {
    set_pon_tm_int_info(iVar1 + 0x4c0);
    netif_napi_add(iVar1,iVar1 + 0x530,pon_tm_net_poll,0x200);
    pon_tm_queue_init();
    *(uint *)(tm_base + 0x104) = *(uint *)(tm_base + 0x104) | 7;
    init_timer_key(pon_tm_timer,0,0,0);
    pon_tm_timer._8_4_ = jiffies + 1;
    pon_tm_timer._16_4_ = pon_tm_timer_func;
    pon_tm_timer._20_4_ = 0;
    add_timer(pon_tm_timer);
    printk("pon_tm net init ok,%d/%d\n",0xd8,0xb0);
    return 0;
  }
  printk("failed to register pon net\n");
  return 0xffffffff;
}

