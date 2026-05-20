// module: switch.ko
// function: sw_acl_l3_hardfast_session_del.part.3 @ 0x12c60
// size: 240 bytes
//

int sw_acl_l3_hardfast_session_del_part_3(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined1 local_b0 [4];
  undefined1 auStack_ac [156];
  
  __memzero(local_b0,0xa0);
  __memzero(&uStack_c4,0x14);
  iVar1 = TO_WAN(*(undefined4 *)(param_1 + 0x18));
  local_b0[0] = iVar1 == 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] direction(0-up 1=dw)=%d\n","sw_acl_l3_hardfast_session_del",local_b0[0]);
  }
  sw_acl_setMtchInfo(param_1,local_b0);
  uStack_c4 = *(undefined4 *)(param_1 + 0x58);
  uStack_c0 = *(undefined4 *)(param_1 + 0x5c);
  local_bc = *(undefined4 *)(param_1 + 0x60);
  local_b8 = *(undefined4 *)(param_1 + 100);
  local_b4 = *(undefined4 *)(param_1 + 0x68);
  iVar1 = zte_api_fast_l3_session_del(auStack_ac,&uStack_c4);
  if (((iVar1 != 0) && (g_switch_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_58414,"sw_acl_l3_hardfast_session_del"), iVar2 != 0)) {
    printk("[%s] sw_acl_del_port_flowconfig failed %d\n","sw_acl_l3_hardfast_session_del",iVar1);
  }
  return iVar1;
}

