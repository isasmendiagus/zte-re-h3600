// module: tm.ko
// function: zte_api_sw_port_get_port_enable @ 0x64524
// size: 172 bytes
//

undefined4
zte_api_sw_port_get_port_enable
          (uint param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  if (4 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][zte_api_sw_port_get_port_enable]input invalid parameter!\n");
    return 1;
  }
  uVar1 = zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),0,param_3,
                       (int)&g_v4_fast_entry_up + param_1,param_4);
  if ((uVar1 & 0x800) == 0) {
    *param_2 = 1;
    return 0;
  }
  if ((uVar1 & 0x800) == 0x800) {
    *param_2 = 0;
    return 0;
  }
  printk("[%s] output: port %d invalid mode!\n","zte_api_sw_port_get_port_enable",param_1);
  return 0xffffffff;
}

