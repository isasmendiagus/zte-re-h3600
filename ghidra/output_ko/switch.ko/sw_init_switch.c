// module: switch.ko
// function: sw_init_switch @ 0x140bc
// size: 192 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_init_switch(void)

{
  uint *puVar1;
  
  sw_reg_set_onu_swcap();
  sw_init_wlan_ssid();
  pdt_ethdriver_init();
  if ((g_pon_work_mode & 0x10) != 0) {
    sw_set_p2pmode();
  }
  chip_tm_init();
  if (g_pon_work_mode == 1) {
    tm_acl_l2_fast_init();
    printk("[SW][sw_init_switch] l2_fast init\n");
  }
  sw_set_default_mulrule();
  sw_set_default_protocol_rule();
  if (g_pon_work_mode == 1) {
    sw_hgu_multi_config_init();
  }
  else {
    sw_sfu_multi_config_init();
  }
  sw_alarm_init();
  printk("[SW][sw_init_switch] reg hff\n");
  l3_hardfastReg();
  sw_qos_init();
  puVar1 = (uint *)(_tm_vlan_check_ena_set * 0x14 + -0xbe2bce8);
  *puVar1 = *puVar1 & 0xfffcffff;
  register_bridge_notifier(sw_bridge_notifier);
  return;
}

