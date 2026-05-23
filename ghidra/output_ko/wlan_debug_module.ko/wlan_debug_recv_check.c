// module: wlan_debug_module.ko
// function: wlan_debug_recv_check @ 0x11200
// size: 344 bytes
//

undefined4 wlan_debug_recv_check(undefined1 *param_1,undefined1 *param_2,undefined1 *param_3)

{
  int iVar1;
  
  if (g_wlan_debug_recv_enable != 0) {
    if (g_wlan_debug_recv_debug != 0) {
      printk("mac1=%02X:%02X:%02X:%02X:%02X:%02X mac2=%02X:%02X:%02X:%02X:%02X:%02X mac3=%02X:%02X:%02X:%02X:%02X:%02X\n"
             ,*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5],*param_2,param_2[1],
             param_2[2],param_2[3],param_2[4],param_2[5],*param_3,param_3[1],param_3[2],param_3[3],
             param_3[4],param_3[5]);
    }
    iVar1 = memcmp(param_2,&g_wlan_debug_recv_mac,6);
    if ((iVar1 == 0) &&
       ((iVar1 = memcmp(param_1,&broadcast_addr,6), iVar1 == 0 ||
        (iVar1 = memcmp(param_3,&broadcast_addr,6), iVar1 == 0)))) {
      g_wlan_debug_recv_count = g_wlan_debug_recv_count + 1;
      return 1;
    }
  }
  return 0;
}

