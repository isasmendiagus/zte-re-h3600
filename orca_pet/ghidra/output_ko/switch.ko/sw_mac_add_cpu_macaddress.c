// module: switch.ko
// function: sw_mac_add_cpu_macaddress @ 0x14e28
// size: 464 bytes
//

int sw_mac_add_cpu_macaddress(int param_1)

{
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  char local_27;
  undefined4 local_26;
  undefined2 local_22;
  
  if (param_1 == 0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_mac_add_cpu_macaddress] input ERROR! ioctl_data_sweth=NULL\n");
    }
  }
  else {
    __memzero(&local_27,7);
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_mac_add_cpu_macaddress] input: mac=%x:%x:%x:%x:%x:%x\n",
             *(undefined1 *)(param_1 + 4),*(undefined1 *)(param_1 + 5),*(undefined1 *)(param_1 + 6),
             *(undefined1 *)(param_1 + 7),*(undefined1 *)(param_1 + 8),*(undefined1 *)(param_1 + 9))
      ;
    }
    pcVar5 = &DAT_0002b99e;
    iVar6 = -1;
    iVar4 = 7;
    local_26 = *(undefined4 *)(param_1 + 4);
    local_22 = *(undefined2 *)(param_1 + 8);
    do {
      pcVar3 = &local_27;
      bVar2 = true;
      bVar1 = false;
      pcVar7 = pcVar5;
      do {
        pcVar3 = pcVar3 + 1;
        if (*pcVar7 != '\0') {
          bVar1 = true;
        }
        if (*pcVar3 != *pcVar7) {
          bVar2 = false;
        }
        pcVar7 = pcVar7 + 1;
      } while (pcVar3 != (char *)((int)&local_22 + 1));
      if (bVar2) {
        if (g_switch_debug_level < 3) {
          return 0;
        }
        printk("[SW][sw_mac_add_cpu_macaddress] output: mac exist alreay\n");
        return 0;
      }
      pcVar5 = pcVar5 + -6;
      if (!bVar1) {
        iVar6 = iVar4;
      }
      iVar4 = iVar4 + -1;
    } while (iVar4 != -1);
    if (iVar6 != -1) {
      local_27 = (char)iVar6;
      *(undefined4 *)(&g_cpu_mac + iVar6 * 6) = *(undefined4 *)(param_1 + 4);
      *(undefined2 *)(&DAT_0002b978 + iVar6 * 6) = *(undefined2 *)(param_1 + 8);
      iVar6 = tm_onu_mac_addr_set(&local_27);
      if (iVar6 != 0) {
        if (g_switch_debug_level == 0) {
          return iVar6;
        }
        printk("[SW][sw_mac_add_cpu_macaddress] return error! error code=0x%x\n",iVar6);
        return iVar6;
      }
      if (2 < g_switch_debug_level) {
        printk("[SW][sw_mac_add_cpu_macaddress] output: SUCCESS\n");
        return 0;
      }
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_mac_add_cpu_macaddress] output: ADD FAIL 5 cpu mac already\n");
      return -1;
    }
  }
  return -1;
}

