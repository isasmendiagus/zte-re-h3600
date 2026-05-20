// module: switch.ko
// function: private_capfun_register @ 0x11500
// size: 792 bytes
//

void private_capfun_register(void)

{
  undefined4 extraout_r2;
  undefined4 in_r3;
  
  fuc_table_node_create(0x3eb,sw_port_set_port_proaction);
  fuc_table_node_create(0x3ec,sw_port_get_port_proaction);
  fuc_table_node_create(0x3ed,sw_port_set_port_802dot1xen);
  fuc_table_node_create(0x3ee,sw_port_get_port_802dot1xen);
  fuc_table_node_create(0x3ef,sw_port_get_port_statistics);
  fuc_table_node_create(0x3f0,sw_port_get_port_vlanstatistics);
  fuc_table_node_create(0x3f1,sw_vlan_add_port_dsvlantranslationentry);
  fuc_table_node_create(0x3f2,sw_vlan_del_port_dsvlantranslationentry);
  fuc_table_node_create(0x3f3,sw_vlan_show_port_dsvlantranslationentry);
  fuc_table_node_create(0x3f4,sw_vlan_add_port_dsmulvlantranslationentry);
  fuc_table_node_create(0x3f5,sw_vlan_del_port_dsmulvlantranslationentry);
  fuc_table_node_create(0x3f7,sw_vlan_set_port_transparent);
  fuc_table_node_create(0x3f8,sw_vlan_get_port_transparent);
  fuc_table_node_create(0x3f9,sw_vlan_set_port_vlanfilter);
  fuc_table_node_create(0x3fa,sw_vlan_get_port_vlanfilter);
  fuc_table_node_create(0x3fb,sw_mac_get_port_learnnum);
  fuc_table_node_create(0x3fc,sw_mac_get_onu_macentrynum);
  fuc_table_node_create(0x3fd,sw_mac_add_cpu_macaddress);
  fuc_table_node_create(0x3fe,sw_mac_del_cpu_macaddress);
  fuc_table_node_create(0x3ff,sw_mac_show_cpu_macaddress);
  fuc_table_node_create(0x400,sw_mac_add_port_macadd_feature);
  fuc_table_node_create(0x401,sw_mac_del_port_macadd_feature);
  fuc_table_node_create(0x402,sw_mac_set_mac_hashmode);
  fuc_table_node_create(0x403,sw_mac_get_mac_hashmode);
  fuc_table_node_create(0x404,sw_qos_set_tcontschedule);
  fuc_table_node_create(0x405,sw_qos_get_tcontschedule);
  fuc_table_node_create(0x406,sw_qos_get_availbktid);
  fuc_table_node_create(0x407,sw_qos_set_trustppqueue);
  fuc_table_node_create(0x408,sw_qos_get_trustppqueue);
  fuc_table_node_create(0x409,sw_qos_set_opritoqueue);
  fuc_table_node_create(0x40a,sw_qos_get_opritoqueue);
  fuc_table_node_create(0x40b,sw_qos_set_mode_schedule);
  fuc_table_node_create(0x40c,sw_qos_set_rcqueue);
  fuc_table_node_create(0x40d,sw_qos_set_queue);
  fuc_table_node_create(0x40e,sw_qos_set_overall_bandwidth);
  fuc_table_node_create(0x40f,qos_info_show);
  fuc_table_node_create(0x410,sw_wancip_set);
  fuc_table_node_create(0x411,sw_wancip_get);
  fuc_table_node_create(0x412,sw_wancip_del);
  fuc_table_node_create(0x413,sw_wlan_idmessid_map);
  fuc_table_node_create(0x414,sw_essid_wlanidm_map);
  fuc_table_node_create(0x415,sw_port_set_cpu_broadcastrate);
  fuc_table_node_create(0x416,sw_port_set_ethdev_carrier);
  fuc_table_node_create(0x417,sw_port_set_cpu_queue_ratelimit);
  fuc_table_node_create(0x418,sw_other_set_area_code);
  fuc_table_node_create(0x41c,sw_other_set_wan_lan_switch);
  fuc_table_node_create(0x3ea,sw_cla_show_aclrule);
  fuc_table_node_create(0x41d,sw_set_trap_cpu_ip);
  fuc_table_node_create(0x47,sw_other_get_port_from_devname,extraout_r2,in_r3);
  return;
}

