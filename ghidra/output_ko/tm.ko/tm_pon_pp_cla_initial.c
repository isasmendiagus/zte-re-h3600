// module: tm.ko
// function: tm_pon_pp_cla_initial @ 0x4dc08
// size: 200 bytes
//

undefined4 tm_pon_pp_cla_initial(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 auStack_48 [12];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_1c;
  
  cla_get_config(auStack_48);
  local_2c = 1;
  local_28 = 1;
  local_24 = 1;
  local_3c = 0;
  local_38 = 0;
  local_30 = 0;
  local_34 = 0;
  local_1c = 0;
  iVar1 = cla_set_config(auStack_48);
  iVar2 = cla_set_outspace_cfg(2,0);
  iVar3 = cla_set_oth_l3_pkt_action_cfg(0);
  iVar4 = cla_set_up_mtu_length_cfg(0x3fff);
  iVar5 = cla_set_dn_mtu_length_cfg(0x3fff);
  iVar6 = cla_set_l3_mtu_length_cfg(0x3fff);
  if ((((((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) || iVar4 != 0) || iVar5 != 0) || iVar6 != 0) &&
     (g_tm_debug_level != 0)) {
    printk("some of the registers in pon_pp_cla_initial initiate falied  , error code=%d!\n");
  }
  printk("api lock init!!\n");
  api_lock_init();
  return 0;
}

