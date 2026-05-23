// module: wlan_debug_module.ko
// function: trp_enable_write @ 0x10acc
// size: 368 bytes
//

uint trp_enable_write(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = __kmalloc(param_3 + 1,0x80d0);
  if (iVar1 == 0) {
    return 0xfffffff4;
  }
  uVar5 = *(uint *)(((uint)&stack0xffffffe8 & 0xffffe000) + 8);
  uVar3 = param_2 + param_3;
  uVar4 = uVar3;
  if (!CARRY4(param_2,param_3)) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar2 = __copy_from_user(iVar1,param_2,param_3);
    if (iVar2 != 0) goto LAB_00010c08;
  }
  else if (param_3 != 0) {
    __memzero(iVar1,param_3,uVar4);
LAB_00010c08:
    kfree(iVar1);
    return 0xfffffff2;
  }
  *(undefined1 *)(iVar1 + param_3) = 0;
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  g_wlan_debug_trp_enable = simple_strtoul(iVar1,0,10);
  if (g_wlan_debug_trp_enable == 1) {
    g_pkts_per_cycle = __aeabi_idiv(g_wlan_debug_trp_flowrate << 0x14,g_wlan_debug_trp_pktlen * 800)
    ;
    iVar2 = mod_timer(g_dev_xmit_timer,jiffies + 1);
    if (iVar2 == 0) {
      printk("func[%s] line[%d] SUCESS!!!,mod_timer OK!\n","_trp_enable_write",0x9a);
    }
  }
  else {
    iVar2 = del_timer(g_dev_xmit_timer);
    if (iVar2 == 0) {
      printk("func[%s] line[%d] SUCESS!!!,del_timer OK!\n","_trp_enable_write",0xa1);
    }
  }
  printk("set enable = [%d]\n",g_wlan_debug_trp_enable);
  kfree(iVar1);
  return param_3;
}

