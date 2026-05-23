// module: tm.ko
// function: pm_set_in_port_rule_valid @ 0x33a7c
// size: 244 bytes
//

undefined4 pm_set_in_port_rule_valid(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  if (g_tm_debug_level < 7) {
    bVar3 = param_3 != 0;
    bVar2 = param_3 == 1;
    if (param_3 < 2) {
      bVar3 = 6 < param_2;
      bVar2 = param_2 == 7;
    }
    if (param_1 < 8 && (!bVar3 || bVar2)) {
LAB_00033ac8:
      iVar1 = tmOnuRegWrite(6,param_1 | param_3 << 3,param_2,pmRegTable);
      if (iVar1 != 0) {
        if ((g_tm_debug_level != 0) &&
           (iVar1 = ___ratelimit(_rs_7215,"pm_set_in_port_rule_valid"), iVar1 != 0)) {
          printk("[TM][pm_set_in_port_rule_valid]reg write failed\n");
        }
        return 0xffffffff;
      }
      return 0;
    }
  }
  else {
    printk("[TM][pm_set_in_port_rule_valid]input: port_num = %d, cfg_num = %d, valid_en = %d\n",
           param_1,param_2,param_3,param_4);
    bVar3 = param_3 != 0;
    bVar2 = param_3 == 1;
    if (param_3 < 2) {
      bVar3 = 6 < param_2;
      bVar2 = param_2 == 7;
    }
    if (param_1 < 8 && (!bVar3 || bVar2)) goto LAB_00033ac8;
    if (6 < g_tm_debug_level) {
      printk("[TM][pm_set_in_port_rule_valid]input invalid parameter!\n");
    }
  }
  return 1;
}

