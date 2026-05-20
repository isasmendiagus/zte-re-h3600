// module: switch.ko
// function: sw_vlan_show_port_dsvlantranslationentry @ 0x1ad40
// size: 64 bytes
//

int sw_vlan_show_port_dsvlantranslationentry(void)

{
  int iVar1;
  
  iVar1 = tm_broadcst_vltrans_table_print_get();
  if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
    printk("sw_vlan_show_port_dsvlantranslationentry return error!\nerror code=0x%x\n",iVar1);
  }
  return iVar1;
}

