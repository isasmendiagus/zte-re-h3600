// module: switch.ko
// function: sw_mac_del_cpu_macaddress @ 0x14ffc
// size: 392 bytes
//

int sw_mac_del_cpu_macaddress(int param_1)

{
  int iVar1;
  bool bVar2;
  char *pcVar3;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  undefined4 local_25;
  undefined2 local_21;
  char local_1f;
  undefined1 auStack_1e [6];
  char *pcVar4;
  
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      iVar6 = -1;
    }
    else {
      printk("[SW][sw_mac_del_cpu_macaddress] input ERROR! ioctl_data_sweth=NULL\n");
      iVar6 = -1;
    }
  }
  else {
    if (2 < g_switch_debug_level) {
      printk("[SW][sw_mac_del_cpu_macaddress] input: mac=%x:%x:%x:%x:%x:%x\n",
             *(undefined1 *)(param_1 + 4),*(undefined1 *)(param_1 + 5),*(undefined1 *)(param_1 + 6),
             *(undefined1 *)(param_1 + 7),*(undefined1 *)(param_1 + 8),*(undefined1 *)(param_1 + 9))
      ;
    }
    iVar6 = 0;
    pcVar5 = &g_cpu_mac;
    __memzero(&local_1f,7);
    local_25 = *(undefined4 *)(param_1 + 4);
    local_21 = *(undefined2 *)(param_1 + 8);
    do {
      bVar2 = true;
      pcVar4 = (char *)&local_25;
      pcVar7 = pcVar5;
      do {
        pcVar3 = pcVar4 + 1;
        if (*pcVar7 != *pcVar4) {
          bVar2 = false;
        }
        pcVar4 = pcVar3;
        pcVar7 = pcVar7 + 1;
      } while (pcVar3 != &local_1f);
      if (bVar2) {
        if (2 < g_switch_debug_level) {
          printk("[SW][sw_mac_del_cpu_macaddress] find the mac, index=%d\n",iVar6);
        }
        __memzero(pcVar5,6);
        __memzero(auStack_1e,6);
        local_1f = (char)iVar6;
        iVar1 = tm_onu_mac_addr_set(&local_1f);
        if (iVar1 != 0) {
          if (g_switch_debug_level == 0) {
            return iVar1;
          }
          printk("[SW][sw_mac_add_cpu_macaddress] return error! error code=0x%x\n",iVar1);
          return iVar1;
        }
        if (2 < g_switch_debug_level) {
          printk("[SW][sw_mac_del_cpu_macaddress] output: SUCCESS\n");
        }
      }
      iVar6 = iVar6 + 1;
      pcVar5 = pcVar5 + 6;
    } while (iVar6 != 8);
    iVar6 = 0;
  }
  return iVar6;
}

