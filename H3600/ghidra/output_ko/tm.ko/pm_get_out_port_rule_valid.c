// module: tm.ko
// function: pm_get_out_port_rule_valid @ 0x33d74
// size: 236 bytes
//

undefined4 pm_get_out_port_rule_valid(uint param_1,uint *param_2)

{
  int iVar1;
  uint local_1c [2];
  
  if (g_tm_debug_level < 7) {
    if (7 < param_1) {
      return 1;
    }
  }
  else {
    printk("[TM][pm_get_out_port_rule_valid]input: port_num = %d\n",param_1);
    if (7 < param_1) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][pm_get_out_port_rule_valid]input invalid parameter!\n");
      return 1;
    }
  }
  iVar1 = 0;
  do {
    tmOnuRegRead(7,local_1c,iVar1,pmRegTable);
    iVar1 = iVar1 + 1;
    if ((local_1c[0] & 7) == param_1) {
      *param_2 = (local_1c[0] << 0x1c) >> 0x1f;
      return 0;
    }
  } while (iVar1 != 8);
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7251,"pm_get_out_port_rule_valid"), iVar1 != 0)) {
    printk("[TM][pm_get_out_port_rule_valid]get port failed\n");
  }
  return 0xffffffff;
}

