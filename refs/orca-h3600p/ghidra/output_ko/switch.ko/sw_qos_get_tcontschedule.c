// module: switch.ko
// function: sw_qos_get_tcontschedule @ 0x18e14
// size: 416 bytes
//

undefined4 sw_qos_get_tcontschedule(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte local_1d;
  undefined4 local_1c;
  
  local_1c = 0;
  local_1d = 0;
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_qos_get_tcontschedule] input ERROR!\nioctl_data_sweth=NULL\n");
    }
    return 0xffffffff;
  }
  uVar4 = *param_1;
  uVar3 = param_1[1];
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_qos_get_tcontschedule] input: tcont_id=%d queue=%d\n",uVar4,uVar3);
  }
  iVar1 = tm_tcont_que_sch_sp_dwwr_mod_get(uVar4,uVar3,&local_1d);
  if (iVar1 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_qos_get_tcontschedule] return error! tm_tcont_que_sch_sp_dwwr_mod_get fail!tcont_id=%d queue=%d\n"
           ,uVar4,uVar3);
    return 0xffffffff;
  }
  iVar1 = tm_tcont_que_sch_weight_get(uVar4,uVar3,&local_1c);
  if (iVar1 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_qos_get_tcontschedule] return error! tm_tcont_que_sch_weight_get fail! tcont_id=%d queue=%d\n"
           ,uVar4,uVar3);
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_qos_get_tcontschedule] output: tcont_id=%d queue=%d mode=%d ",uVar4,uVar3,
           local_1d);
    uVar2 = (uint)local_1d;
    if (uVar2 == 0) {
      if (g_switch_debug_level < 3) goto LAB_00018eac;
      printk(&_LC12);
    }
    else {
      if (g_switch_debug_level < 3) goto LAB_00018eac;
      printk("dwrr ");
    }
    if (2 < g_switch_debug_level) {
      printk("weight=%d\n",local_1c);
    }
  }
  uVar2 = (uint)local_1d;
LAB_00018eac:
  param_1[2] = uVar2;
  param_1[3] = local_1c;
  return 0;
}

