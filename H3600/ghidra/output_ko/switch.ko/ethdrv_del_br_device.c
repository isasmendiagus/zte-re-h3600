// module: switch.ko
// function: ethdrv_del_br_device @ 0x10438
// size: 72 bytes
//

undefined4 ethdrv_del_br_device(void)

{
  undefined4 uVar1;
  
  uVar1 = g_sw_netInfo._4_4_;
  if (g_sw_netInfo._4_4_ != 0) {
    unregister_netdev(g_sw_netInfo._4_4_);
    free_netdev(uVar1);
    g_sw_netInfo._4_4_ = 0;
    g_sw_netInfo[0] = g_sw_netInfo[0] + -1;
    return 0;
  }
  return 0xffffffff;
}

