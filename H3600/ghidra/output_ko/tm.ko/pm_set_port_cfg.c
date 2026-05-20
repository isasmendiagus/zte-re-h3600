// module: tm.ko
// function: pm_set_port_cfg @ 0x342bc
// size: 184 bytes
//

undefined4 pm_set_port_cfg(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (((1 < param_1[1]) || (uVar3 = *param_1, 1 < uVar3)) || (uVar1 = param_1[2], 7 < uVar1)) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][pm_set_port_cfg]input invalid parameter!\n");
    return 1;
  }
  if (uVar3 == 0) {
    iVar2 = pm_set_in_port_rule_valid();
  }
  else {
    iVar2 = pm_set_out_port_rule_valid(uVar1,uVar1,param_1[1],uVar3,param_4);
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar2 = ___ratelimit(_rs_7301,"pm_set_port_cfg"), iVar2 != 0)) {
    printk("[TM][pm_set_port_cfg]failed\n");
  }
  return 0xffffffff;
}

