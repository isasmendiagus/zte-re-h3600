// module: switch.ko
// function: sw_vlan_del_port_dsvlantranslationentry @ 0x1ab80
// size: 444 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_vlan_del_port_dsvlantranslationentry(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      iVar1 = -1;
    }
    else {
      printk("sw_vlan_del_port_dsvlantranslationentry input ERROR!\nioctl_data_sweth=NULL\n");
      iVar1 = -1;
    }
  }
  else {
    uVar2 = param_1[1];
    if ((2 < g_switch_debug_level) &&
       (printk("sw_vlan_del_port_dsvlantranslationentry input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\n"
               ,*param_1,uVar2,param_1[2],param_1[3]), 2 < g_switch_debug_level)) {
      printk("[SW][sw_vlan_del_port_dsvlantranslationentry] input:\tvalid=%d\tvlan_en=%d\tuni_pri=%d\tpon_pri=%d\tpri_use=%d\tpri_en=%d\n"
             ,*(undefined1 *)(param_1 + 4),*(undefined1 *)((int)param_1 + 0x11),
             *(undefined1 *)((int)param_1 + 0x12),*(undefined1 *)((int)param_1 + 0x13),
             *(undefined1 *)(param_1 + 5),*(undefined1 *)((int)param_1 + 0x15));
    }
    if (uVar2 < _tm_port_unknwn_multicast_floodport_set) {
      __memzero(&local_38,0x18);
      local_2c = (uint)(byte)tm_set_p2pmode[uVar2];
      local_34 = *param_1;
      local_30 = param_1[3];
      local_38 = param_1[2];
      local_25 = *(undefined1 *)((int)param_1 + 0x13);
      local_23 = *(undefined1 *)((int)param_1 + 0x15);
      local_24 = *(undefined1 *)(param_1 + 5);
      local_26 = *(undefined1 *)((int)param_1 + 0x12);
      local_27 = *(undefined1 *)((int)param_1 + 0x11);
      local_28 = 0;
      if (2 < g_switch_debug_level) {
        printk(
              "[SW][sw_vlan_del_port_dsvlantranslationentry] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\tpon_pri=%d\tpri_en=%d\tpri_use=%d\nuni_pri=%d\tvalid=%d\tvlan_en=%d\n"
              );
      }
      iVar1 = tm_broadcst_vltrans_table_delete_set(&local_38);
      if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
        printk("sw_vlan_del_port_dsvlantranslationentry return error!\nerror code=0x%x\n",iVar1);
      }
    }
    else {
      printk("[%s]%d input port error!\n","sw_vlan_del_port_dsvlantranslationentry",0x17d);
      iVar1 = -1;
    }
  }
  return iVar1;
}

