// module: tm.ko
// function: zte_api_sw_set_cla_other_l3pkt_action @ 0x63b94
// size: 64 bytes
//

int zte_api_sw_set_cla_other_l3pkt_action(void)

{
  int iVar1;
  
  iVar1 = cla_set_oth_l3_pkt_action_cfg();
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("cla_set_oth_l3_pkt_action_cfg falied  , error code=%d!\n",iVar1);
  }
  return iVar1;
}

