// module: switch.ko
// function: sw_acl_l3_hardfast_flowstatus @ 0x12f5c
// size: 180 bytes
//

uint sw_acl_l3_hardfast_flowstatus(int param_1)

{
  uint uVar1;
  byte local_25;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_25 = 0;
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
    local_24 = *(undefined4 *)(param_1 + 0x58);
    local_20 = *(undefined4 *)(param_1 + 0x5c);
    local_1c = *(undefined4 *)(param_1 + 0x60);
    local_18 = *(undefined4 *)(param_1 + 100);
    local_14 = *(undefined4 *)(param_1 + 0x68);
    zte_api_fast_l3_session_use(0,&local_24,&local_25);
    if (2 < g_switch_debug_level) {
      printk("[%s] status = %d \n","sw_acl_l3_hardfast_flowstatus",local_25);
    }
    uVar1 = (uint)local_25;
  }
  return uVar1;
}

