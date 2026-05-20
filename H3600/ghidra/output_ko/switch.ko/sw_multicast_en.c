// module: switch.ko
// function: sw_multicast_en @ 0x170e8
// size: 472 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_multicast_en(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_multicast_en] input:p_en = %d\n",param_1,param_3,g_switch_debug_level,param_4);
  }
  if (param_1 != 1) {
    iVar1 = tm_port_unknwn_multicast_flood_set(5,1);
    if (iVar1 != 0) {
      printk("[sw_multicast_en] tm_port_unknwn_multicast_flood_set OUT Fail!\n");
    }
    uVar2 = 0;
    do {
      if ((((DAT_0002c0e6 | DAT_0002c0e2) | _zte_api_sw_mac_set_port_learnlimit) &
          1 << (uVar2 & 0xff)) != 0) {
        iVar1 = tm_port_unknwn_multicast_fwd_set(uVar2);
        if (iVar1 != 0) {
          printk("[sw_multicast_en] tm_port_unknwn_multicast_fwd_set OUT Fail!\n");
        }
        iVar1 = tm_port_unknwn_multicast_floodport_set(5,1,uVar2);
        if (iVar1 != 0) {
          printk("[sw_multicast_en] tm_port_unknwn_multicast_floodport_set OUT Fail!\n");
        }
        iVar1 = tm_port_dft_multicst_vltrans_set(uVar2,1);
        if (iVar1 != 0) {
          printk("[sw_multicast_en] tm_port_dft_multicst_vltrans_set OUT Fail!\n");
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != 8);
    return;
  }
  iVar1 = tm_port_unknwn_multicast_flood_set(5,0);
  if (iVar1 != 0) {
    printk("[sw_multicast_en] tm_port_unknwn_multicast_flood_set OUT Fail!\n");
  }
  uVar2 = 0;
  do {
    if ((((DAT_0002c0e6 | DAT_0002c0e2) | _zte_api_sw_mac_set_port_learnlimit) & 1 << (uVar2 & 0xff)
        ) != 0) {
      iVar1 = tm_port_unknwn_multicast_fwd_set(uVar2,0);
      if (iVar1 != 0) {
        printk("[sw_multicast_en] tm_port_unknwn_multicast_fwd_set OUT Fail!\n");
      }
      iVar1 = tm_port_unknwn_multicast_floodport_set(5,0,uVar2);
      if (iVar1 != 0) {
        printk("[sw_multicast_en] tm_port_unknwn_multicast_floodport_set OUT Fail!\n");
      }
      iVar1 = tm_port_dft_multicst_vltrans_set(uVar2,0);
      if (iVar1 != 0) {
        printk("[sw_multicast_en] tm_port_dft_multicst_vltrans_set OUT Fail!\n");
      }
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 8);
  return;
}

