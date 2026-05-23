// module: switch.ko
// function: sw_mac_show_cpu_macaddress @ 0x15184
// size: 176 bytes
//

undefined4 sw_mac_show_cpu_macaddress(int param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[SW][sw_mac_show_cpu_macaddress] input ERROR! ioctl_data_sweth=NULL\n");
      uVar1 = 0xffffffff;
    }
  }
  else {
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_mac_show_cpu_macaddress] output:\n");
    }
    puVar2 = &g_cpu_mac;
    iVar3 = 0;
    do {
      iVar4 = iVar3 + 1;
      printk("index=%d cpu mac=%x:%x:%x:%x:%x:%x\n",iVar3,*puVar2,puVar2[1],puVar2[2],puVar2[3],
             puVar2[4],puVar2[5]);
      puVar2 = puVar2 + 6;
      iVar3 = iVar4;
    } while (iVar4 != 8);
    uVar1 = 0;
  }
  return uVar1;
}

