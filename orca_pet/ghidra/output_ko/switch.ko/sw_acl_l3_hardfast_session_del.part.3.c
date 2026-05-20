// module: switch.ko
// function: sw_acl_l3_hardfast_session_del.part.3 @ 0x12acc
// size: 240 bytes
//

int sw_acl_l3_hardfast_session_del_part_3(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined1 local_b4 [4];
  undefined1 auStack_b0 [160];
  
  __memzero(local_b4,0xa4);
  __memzero(&uStack_cc,0x18);
  iVar1 = TO_WAN(*(undefined4 *)(param_1 + 0x18));
  local_b4[0] = iVar1 == 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] direction(0-up 1=dw)=%d\n","sw_acl_l3_hardfast_session_del",local_b4[0]);
  }
  sw_acl_setMtchInfo(param_1,local_b4);
  uStack_cc = *(undefined4 *)(param_1 + 0x58);
  uStack_c8 = *(undefined4 *)(param_1 + 0x5c);
  local_c4 = *(undefined4 *)(param_1 + 0x60);
  local_c0 = *(undefined4 *)(param_1 + 100);
  local_bc = *(undefined4 *)(param_1 + 0x68);
  iVar1 = zte_api_fast_l3_session_del(auStack_b0,&uStack_cc);
  if (((iVar1 != 0) && (g_switch_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_58264,"sw_acl_l3_hardfast_session_del"), iVar2 != 0)) {
    printk("[%s] sw_acl_del_port_flowconfig failed %d\n","sw_acl_l3_hardfast_session_del",iVar1);
  }
  return iVar1;
}

