// module: switch.ko
// function: sw_acl_l3_hardfast_session_del @ 0x12e80
// size: 64 bytes
//

undefined4
sw_acl_l3_hardfast_session_del(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    uVar1 = sw_acl_l3_hardfast_session_del_part_3();
    return uVar1;
  }
  if (g_switch_debug_level != 0) {
    printk("[%s] input ERROR: ptSession=NULL\n","sw_acl_l3_hardfast_session_del",param_3,
           g_switch_debug_level,param_4);
  }
  return 0xffffffff;
}

