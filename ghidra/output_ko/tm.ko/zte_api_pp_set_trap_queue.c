// module: tm.ko
// function: zte_api_pp_set_trap_queue @ 0x63f10
// size: 152 bytes
//

undefined4
zte_api_pp_set_trap_queue(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 != 0) {
    iVar2 = tm_protocol_pkt_limit_map_set(5);
    if (iVar2 == 0) {
      return 0;
    }
LAB_00063f7c:
    if (g_tm_debug_level != 0) {
      printk("[TM][tm_cla_cpu_queueid_set] failed\n");
    }
    return 0xffffffff;
  }
  iVar3 = 1;
  iVar2 = 0;
  do {
    if (iVar2 != 5) {
      iVar1 = tm_protocol_pkt_limit_map_set(iVar2,param_2,param_3,0,param_4);
      if (iVar1 != 0) goto LAB_00063f7c;
      if (iVar3 == 8) {
        return 0;
      }
    }
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 1;
  } while( true );
}

