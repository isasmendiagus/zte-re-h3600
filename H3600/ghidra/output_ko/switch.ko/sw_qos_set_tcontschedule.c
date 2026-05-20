// module: switch.ko
// function: sw_qos_set_tcontschedule @ 0x18c20
// size: 356 bytes
//

undefined4 sw_qos_set_tcontschedule(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_qos_set_tcontschedule] input ERROR!\nioctl_data_sweth=NULL\n");
    return 0xffffffff;
  }
  uVar3 = *param_1;
  uVar2 = param_1[1];
  uVar5 = param_1[3];
  uVar4 = param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[SW][sw_qos_set_tcontschedule] input: tcont_id=%d queue=%d mod=%d weight=%d\n",uVar3,
           uVar2,uVar4,uVar4);
    if (param_1[2] == 0) {
      if (g_switch_debug_level < 3) goto LAB_00018c54;
      printk(&_LC12);
    }
    else {
      if (g_switch_debug_level < 3) goto LAB_00018c54;
      printk("dwrr ");
    }
    if (2 < g_switch_debug_level) {
      printk("weight=%d\n",uVar5);
    }
  }
LAB_00018c54:
  iVar1 = tm_tcont_que_sch_sp_dwwr_mod_set(uVar3,uVar2,uVar4 & 0xff);
  if (iVar1 == 0) {
    iVar1 = tm_tcont_que_sch_weight_set(uVar3,uVar2,uVar5);
    if (iVar1 == 0) {
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_qos_set_tcontschedule] return error! tm_tcont_que_sch_weight_set fail! tcont_id=%d quene=%d weight=%d\n"
             ,uVar3,uVar2,uVar5);
    }
  }
  else if (g_switch_debug_level != 0) {
    printk("[SW][sw_qos_set_tcontschedule] return error! tm_tcont_que_sch_sp_dwwr_mod_set fail! tcont_id=%d quene=%d mode=%d\n"
           ,uVar3,uVar2,uVar4);
    return 0xffffffff;
  }
  return 0xffffffff;
}

