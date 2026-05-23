// module: switch.ko
// function: sw_acl_l3_hardfast_session_add @ 0x12d7c
// size: 104 bytes
//

undefined4
sw_acl_l3_hardfast_session_add(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  if (2 < g_switch_debug_level) {
    printk("enter sw_acl_l3_hardfast_session_add\n");
    param_2 = extraout_r1;
    param_3 = extraout_r2;
  }
  if (param_1 != 0) {
    uVar1 = sw_acl_l3_hardfast_session_add_part_1(param_1,param_2,param_3,param_4);
    return uVar1;
  }
  if (g_switch_debug_level != 0) {
    printk("[%s] input ERROR: ptSession=NULL\n","sw_acl_l3_hardfast_session_add");
  }
  return 0xffffffff;
}

