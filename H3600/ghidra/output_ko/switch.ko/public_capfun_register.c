// module: switch.ko
// function: public_capfun_register @ 0x11818
// size: 800 bytes
//

void public_capfun_register(void)

{
  sw_public_port_vlan_func_reg
            (sw_vlan_set_port_inframemode,sw_vlan_get_port_inframemode,sw_vlan_set_port_pvid,
             sw_vlan_get_port_pvid,sw_vlan_set_port_vlancfg,sw_vlan_get_port_vlancfg,
             sw_set_mflow_config);
  sw_public_port_cfg_func_reg
            (sw_port_set_port_enable,sw_port_get_port_enable,sw_port_set_port_flowcontrol,
             sw_port_get_port_flowcontrol,sw_port_set_port_isolate,sw_port_get_port_isolate,
             sw_port_set_port_isolatemask,sw_port_get_port_isolatemask,sw_port_set_port_floodcontrol
             ,sw_port_get_port_floodcontrol,sw_port_set_port_floodcontrolmask,
             sw_port_get_port_floodcontrolmask,sw_port_set_port_linkmode,sw_port_get_port_linkmode,
             sw_port_get_port_linkstate,sw_port_set_port_mirror,sw_port_get_port_mirror,
             sw_port_set_port_loopback,sw_port_get_port_loopback);
  sw_public_port_ratelimit_func_reg
            (sw_port_set_port_ratelimit,sw_port_get_port_ratelimit,sw_port_set_port_multicastrate,
             sw_port_get_port_multicastrate,sw_port_set_port_broadcastrate,
             sw_port_get_port_broadcastrate);
  sw_public_onu_mactable_func_reg
            (sw_mac_set_onu_agingtime,sw_mac_get_onu_agingtime,sw_mac_set_port_learnlimit,
             sw_mac_get_port_learnlimit,sw_mac_add_port_macaddress,sw_mac_del_port_macaddress,
             sw_mac_set_port_macfiltermode,sw_mac_get_port_macfiltermode,
             sw_mac_add_port_macfilterentry,sw_mac_del_port_macfilterentry,
             sw_mac_get_port_macfilterentry,sw_mac_show_macaddress,sw_mac_clear_macaddress,
             sw_mac_show_port_mactable,sw_mac_clear_port_mactable);
  sw_public_onu_qos_func_reg
            (sw_qos_set_port_schedule,sw_qos_get_port_schedule,sw_acl_add_port_flowconfig,
             sw_acl_del_port_flowconfig,sw_acl_get_port_flowconfig);
  sw_public_onu_statistics_func_reg
            (sw_port_get_port_statistics1,sw_port_get_port_statistics2,sw_port_get_port_statistics3,
             sw_port_get_port_statistics4,sw_port_clear_port_count,sw_port_clear_port_count_byportid
             ,sw_port_get_port_rmonstats);
  sw_public_onu_other_func_reg
            (sw_mac_set_onu_stpaction,sw_mac_get_onu_stpaction,sw_mac_set_onu_proaction,
             sw_mac_get_onu_proaction,sw_other_set_onu_mtu,sw_other_get_onu_mtu,sw_reg_set_readreg,
             sw_reg_set_writereg,sw_phy_reg_set_readreg,sw_phy_reg_set_writereg);
  return;
}

