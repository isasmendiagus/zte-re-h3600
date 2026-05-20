// module: switch.ko
// function: sw_qos_set_overall_bandwidth @ 0x19760
// size: 360 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sw_qos_set_overall_bandwidth(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[%s] the input para is null\n","sw_qos_set_overall_bandwidth");
      return -1;
    }
    return -1;
  }
  if (1 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_qos_set_overall_bandwidth","Scheduler.overall",*param_1);
  }
  uVar3 = *param_1;
  if ((g_pon_work_mode & 0x10) == 0) {
    uVar2 = (uint)g_tcont_start;
    if (g_tcont_size <= uVar2) {
      iVar1 = -1;
      goto LAB_000197ec;
    }
    do {
      iVar1 = tm_tcont_sharp_set(uVar2,uVar3);
      uVar2 = uVar2 + 1;
    } while ((int)uVar2 < (int)(uint)g_tcont_size);
  }
  else {
    iVar1 = sw_qos_vdsl_up();
    if (iVar1 == 0) {
      printk("g_sw_cap.sw_wan_port = %d\n",_tm_vlan_check_ena_set);
      iVar1 = zte_api_sw_port_set_port_ratelimit(_tm_vlan_check_ena_set & 0xff,1,1,1,uVar3,0,1);
    }
    else {
      iVar1 = tm_tcont_sharp_set(0,uVar3);
    }
  }
  if (iVar1 == 0) {
    return 0;
  }
LAB_000197ec:
  if (g_switch_debug_level != 0) {
    printk("[%s] the error code is %dl\n","sw_qos_set_overall_bandwidth",iVar1);
  }
  return iVar1;
}

