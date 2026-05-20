// module: tm.ko
// function: zte_api_fast_l3_session_clr @ 0x6383c
// size: 152 bytes
//

undefined4 zte_api_fast_l3_session_clr(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar4 = 0;
  puVar5 = (undefined4 *)((int)&g_fast_entry_v6 + 4);
  do {
    puVar5 = puVar5 + 1;
    puVar3 = (undefined1 *)*puVar5;
    puVar2 = puVar3;
    while (puVar2 != (undefined1 *)0x0) {
      iVar1 = tm_del_acl_flow_rule(puVar3 + 0x30,*puVar3);
      if (iVar1 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[%s] tm_del_acl_flow_rule failed %d\n","zte_sw_api.c");
        return 0xffffffff;
      }
      tm_delete_fast_rule_node(iVar4,puVar3);
      puVar3 = *(undefined1 **)(puVar3 + 0x48);
      puVar2 = (undefined1 *)*puVar5;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x200);
  return 0;
}

