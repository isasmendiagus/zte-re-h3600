// module: tm.ko
// function: tm_set_p2pmode @ 0x464c0
// size: 52 bytes
//

undefined4 tm_set_p2pmode(uint param_1)

{
  lan_up_port = param_1;
  printk("lan_up_port=0x%x\n",param_1);
  tm_set_pp_wan_cfg(lan_up_port & 0xff);
  return 0;
}

