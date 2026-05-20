// module: switch.ko
// function: sw_acl_l3_hardfast_flowstatus @ 0x12dc8
// size: 188 bytes
//

uint sw_acl_l3_hardfast_flowstatus(int param_1)

{
  uint uVar1;
  byte local_29;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_29 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[%s] input ERROR: ptSession=NULL\n","sw_acl_l3_hardfast_flowstatus");
      uVar1 = 0xffffffff;
    }
  }
  else {
    local_28 = *(undefined4 *)(param_1 + 0x58);
    local_24 = *(undefined4 *)(param_1 + 0x5c);
    local_20 = *(undefined4 *)(param_1 + 0x60);
    local_1c = *(undefined4 *)(param_1 + 100);
    local_18 = *(undefined4 *)(param_1 + 0x68);
    local_14 = *(undefined4 *)(param_1 + 0x6c);
    zte_api_fast_l3_session_use(0,&local_28,&local_29);
    if (2 < g_switch_debug_level) {
      printk("[%s] status = %d \n","sw_acl_l3_hardfast_flowstatus",local_29);
    }
    uVar1 = (uint)local_29;
  }
  return uVar1;
}

