// module: switch.ko
// function: sw_vlan_del_port_dsmulvlantranslationentry @ 0x1b2a4
// size: 592 bytes
//

undefined4 sw_vlan_del_port_dsmulvlantranslationentry(undefined4 *param_1)

{
  int iVar1;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  undefined4 local_4c;
  undefined1 local_48;
  undefined1 local_47;
  char local_46;
  byte local_45;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 auStack_40 [8];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  undefined1 local_28;
  undefined1 local_27;
  byte local_26;
  undefined1 local_25;
  char local_24;
  undefined1 local_23;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_vlan_del_port_dsmulvlantranslationentry] input ERROR! ioctl_data_sweth=NULL\n"
            );
      return 0xffffffff;
    }
  }
  else {
    if ((2 < g_switch_debug_level) &&
       (printk("[SW][sw_vlan_del_port_dsmulvlantranslationentry] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\n"
               ,*param_1,param_1[1],param_1[2],param_1[3]), 2 < g_switch_debug_level)) {
      printk("[SW][sw_vlan_del_port_dsmulvlantranslationentry] input:\tvalid=%d\tvlan_en=%d\tuni_pri=%d\tpon_pri=%d\tpri_use=%d\tpri_en=%d\n"
             ,*(undefined1 *)(param_1 + 4),*(undefined1 *)((int)param_1 + 0x11),
             *(undefined1 *)((int)param_1 + 0x12),*(undefined1 *)((int)param_1 + 0x13),
             *(undefined1 *)(param_1 + 5),*(undefined1 *)((int)param_1 + 0x15));
    }
    __memzero(auStack_40,0x20);
    local_26 = *(byte *)((int)param_1 + 0x13);
    if (*(char *)((int)param_1 + 0x15) == '\0') {
      if (local_26 == 8) {
        local_27 = 0;
        local_25 = 0;
      }
      else if (local_26 < 8) {
        local_27 = 1;
        local_25 = 0;
      }
    }
    else if (local_26 == 8) {
      local_27 = 0;
      local_25 = 1;
    }
    else if (local_26 < 8) {
      local_27 = 1;
      local_25 = 1;
    }
    local_2c = param_1[3];
    local_38 = *param_1;
    local_34 = param_1[1];
    local_24 = *(char *)((int)param_1 + 0x12);
    local_30 = param_1[2];
    if (local_2c < 2) {
      local_30 = local_38;
    }
    local_28 = 0;
    if (local_26 == 8) {
      local_26 = 0;
    }
    local_23 = *(undefined1 *)((int)param_1 + 0x11);
    if (local_24 == '\b') {
      local_24 = '\0';
    }
    if (2 < g_switch_debug_level) {
      printk(
            "[SW][sw_vlan_del_port_dsmulvlantranslationentry] input:\tponvlan=%d\tport=%d\tunivlan=%d\taction=%d\tpon_pri=%d\tpri_en=%d\tpri_use=%d\nuni_pri=%d\tvalid=%d\tvlan_en=%d\n"
            );
    }
    local_58 = local_30;
    local_54 = local_38;
    local_50 = local_2c;
    local_4c = local_34;
    local_48 = local_28;
    local_47 = local_23;
    local_46 = local_24;
    local_45 = local_26;
    local_44 = local_25;
    local_43 = local_27;
    iVar1 = tm_multicst_vltrans_table_delete_set(&local_58);
    if (iVar1 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][tm_multicst_vltrans_table_delete_set]  portlist3 FAIL!!!\n");
    }
  }
  return 0xffffffff;
}

