// module: tm.ko
// function: zte_api_sw_port_set_port_linkmode @ 0x64874
// size: 352 bytes
//

undefined4 zte_api_sw_port_set_port_linkmode(uint param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  
  if (4 < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][zte_api_sw_port_set_port_linkmode]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),0);
  if (((param_2 != 1) && (param_3 != 0 || param_4 != 0)) && (param_3 != 0 || param_4 != 1)) {
    bVar1 = param_3 == 1;
    if (((!bVar1 || param_4 != 0) && (!bVar1 || param_4 != 1)) &&
       ((param_3 != 2 || param_4 != 0 && (param_3 != 2 || param_4 != 1)))) {
      printk("[%s] input invalid mode\n","zte_api_sw_port_set_port_linkmode",bVar1);
      return 0xffffffff;
    }
  }
  zx_mdio_write(*(undefined1 *)((int)&uni_phy + param_1),0);
  return 0;
}

