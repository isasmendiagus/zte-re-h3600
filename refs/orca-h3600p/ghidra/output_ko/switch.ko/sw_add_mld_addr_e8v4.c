// module: switch.ko
// function: sw_add_mld_addr_e8v4 @ 0x1ff88
// size: 420 bytes
//

undefined4 sw_add_mld_addr_e8v4(undefined4 *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  uint local_50;
  int aiStack_4c [4];
  int local_3c [7];
  
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&local_64,0x10);
    local_64 = *param_1;
    local_60 = param_1[1];
    local_5c = param_1[2];
    local_58 = param_1[3];
    if (2 < g_switch_debug_level) {
      printk("sw_add_mld_addr_e8v4 portname %s\n",&local_64);
    }
    iVar1 = get_sw_port_from_devname(&local_64,&local_68,1);
    if (iVar1 == 0) {
      iVar1 = 1 << (local_68 & 0xff);
      __memzero(&local_54,0x34);
      uVar5 = *(ushort *)(param_1 + 4) & 0xfff;
      if (2 < g_switch_debug_level) {
        printk("sw_add_mld_addr_e8v4 dip:");
      }
      puVar2 = (undefined1 *)((int)param_1 + 0x22);
      piVar3 = aiStack_4c;
      uVar6 = g_switch_debug_level;
      do {
        puVar2 = puVar2 + -1;
        piVar4 = (int *)((int)piVar3 + 1);
        *(undefined1 *)piVar3 = *puVar2;
        if (2 < uVar6) {
          printk("%2.2x.\n");
          uVar6 = g_switch_debug_level;
        }
        piVar3 = piVar4;
      } while (piVar4 != local_3c);
      if (2 < uVar6) {
        printk("\nsw_add_mld_addr_e8v4 portMsk 0x%8.8x, vlan %d\n",iVar1,uVar5);
      }
      local_53 = 0;
      local_54 = 1;
      local_52 = 1;
      local_50 = uVar5;
      local_3c[0] = iVar1;
      tm_ipv6table_add_set(&local_54);
      sw_mld_mulrule_deal(aiStack_4c,uVar5,1);
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("get_sw_port_from_devname curPort ERROR: portname=%s\n",&local_64);
    }
  }
  return 0xffffffff;
}

