// module: wlan_debug_module.ko
// function: trp_xmitdev_write @ 0x10550
// size: 368 bytes
//

uint trp_xmitdev_write(int param_1,uint param_2,uint param_3)

{
  char *__s;
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *puVar6;
  uint local_28;
  uint local_24;
  uint local_20;
  
  __s = (char *)__kmalloc(param_3 + 1,0x80d0);
  if (__s == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar5 = *(uint *)(((uint)&local_28 & 0xffffe000) + 8);
  uVar3 = param_2 + param_3;
  uVar4 = uVar3;
  if (!CARRY4(param_2,param_3)) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar1 = __copy_from_user(__s,param_2,param_3);
    if (iVar1 != 0) goto LAB_00010694;
  }
  else if (param_3 != 0) {
    __memzero(__s,param_3,uVar4);
LAB_00010694:
    kfree(__s);
    return 0xfffffff2;
  }
  __s[param_3] = '\0';
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  sscanf(__s,"%31s",g_wlan_debug_trp_xmitdev);
  printk("set xmitdev = [%s]\n",g_wlan_debug_trp_xmitdev);
  iVar1 = dev_get_by_name(&init_net,g_wlan_debug_trp_xmitdev);
  if (iVar1 == 0) {
    printk("###########get [%s] net_device fail!!!!!!!!!!!!!!",g_wlan_debug_trp_xmitdev);
  }
  else {
    puVar6 = *(undefined1 **)(iVar1 + 0x1dc);
    local_28 = (uint)(byte)puVar6[3];
    local_24 = (uint)(byte)puVar6[4];
    local_20 = (uint)(byte)puVar6[5];
    printk("dev->dev_addr[%02x:%02x:%02x:%02x:%02x:%02x]\n",*puVar6,puVar6[1],puVar6[2]);
    g_wlan_debug_trp_srcmac._0_4_ = **(undefined4 **)(iVar1 + 0x1dc);
    g_wlan_debug_trp_srcmac._4_2_ = *(undefined2 *)(*(undefined4 **)(iVar1 + 0x1dc) + 1);
    disableIRQinterrupts();
    iVar2 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
    *(int *)(iVar2 + *(int *)(iVar1 + 0x280)) = *(int *)(iVar2 + *(int *)(iVar1 + 0x280)) + -1;
  }
  kfree(__s);
  return param_3;
}

