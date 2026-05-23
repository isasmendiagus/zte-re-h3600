// module: switch.ko
// function: sw_mac_get_port_learnnum @ 0x14c98
// size: 196 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_mac_get_port_learnnum(uint *param_1)

{
  int iVar1;
  uint uVar2;
  uint local_14;
  
  uVar2 = *param_1;
  local_14 = 0;
  if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
    iVar1 = tm_mac_learning_number_get(tm_set_p2pmode[uVar2],&local_14);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("sw_mac_get_port_learnnum output:\nport=%d\nlearnnum=%d\n",uVar2,local_14);
      }
      iVar1 = 0;
      param_1[1] = local_14;
    }
    else if (g_switch_debug_level != 0) {
      printk("sw_mac_get_port_learnnum return error!\nerror code=%x\n",iVar1);
    }
  }
  else {
    printk("[%s]%d input port error!\n","sw_mac_get_port_learnnum",0xfb);
    iVar1 = -1;
  }
  return iVar1;
}

