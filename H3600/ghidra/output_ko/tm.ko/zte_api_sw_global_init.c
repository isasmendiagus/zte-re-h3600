// module: tm.ko
// function: zte_api_sw_global_init @ 0x6520c
// size: 556 bytes
//

undefined4 zte_api_sw_global_init(undefined4 *param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 local_24 [2];
  
  iVar2 = sbrg_set_table_sel(*param_1);
  if ((((iVar2 != 0) || (iVar2 = sbrg_set_hash_mode(param_1[1]), iVar2 != 0)) ||
      (iVar2 = sbrg_set_hash_collision_pktdeal(param_1[2]), iVar2 != 0)) ||
     ((iVar2 = sbrg_set_macaddr_exchange_md(param_1[3]), iVar2 != 0 ||
      (iVar2 = sbrg_set_multicst_md(*(undefined1 *)(param_1 + 4)), iVar2 != 0)))) {
    return 0xffffffff;
  }
  if (param_1[5] != 0) {
    uVar3 = 0;
    if (param_1[5] != 1) goto LAB_00065278;
    iVar2 = sbrg_set_multi_mac_vlan_mode(1);
    if ((iVar2 != 0) && (g_tm_debug_level != 0)) {
      printk("[TM][sbrg_set_multi_mac_vlan_mode] set failed\n");
    }
    iVar2 = sbrg_set_multi_mac_hash_mode(1);
    if (((iVar2 != 0) && (g_tm_debug_level != 0)) &&
       (printk("[TM][sbrg_set_multi_mac_hash_mode] set failed\n"), g_tm_debug_level != 0)) {
      printk("[TM][spa_set_multi_mode] set failed\n");
    }
  }
  uVar3 = 1;
LAB_00065278:
  iVar2 = tm_multivlan_mode_set(uVar3);
  if ((iVar2 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][tm_multivlan_mode_set] set failed\n");
  }
  uVar1 = *(undefined2 *)(param_1 + 7);
  iVar2 = 0;
  do {
    iVar4 = zte_api_sw_other_set_onu_mtu(iVar2,uVar1);
    if (iVar4 != 0) {
      printk("set port %d mtu err %d\n",iVar2);
      return 0xffffffff;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 5);
  iVar2 = 0;
  do {
    iVar4 = 0;
    puVar7 = param_1 + 7;
    do {
      puVar7 = (undefined4 *)((int)puVar7 + 2);
      iVar5 = tm_tpid_vlu_select_get(*(undefined2 *)puVar7,local_24);
      if (iVar5 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][tm_tpid_vlu_select_get] get failed\n");
        return 0xffffffff;
      }
      iVar5 = iVar4;
      do {
        iVar6 = iVar5 + 4;
        iVar5 = tm_in_port_tpid_select_set(iVar2,local_24[0],iVar5);
        if (iVar5 != 0) {
          if (g_tm_debug_level == 0) {
            return 0xffffffff;
          }
          printk("[TM][tm_tpid_select_set] set failed\n");
          return 0xffffffff;
        }
        iVar5 = iVar6;
      } while (iVar6 != iVar4 + 0x10);
      iVar4 = iVar4 + 1;
    } while (iVar4 != 4);
    iVar2 = iVar2 + 1;
  } while (iVar2 != 9);
  return 0;
}

