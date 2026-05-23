// module: tm.ko
// function: pm_get_port_cfg @ 0x3437c
// size: 200 bytes
//

undefined4 pm_get_port_cfg(uint *param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint local_c;
  
  if ((*param_1 < 2) && (param_1[2] < 8)) {
    if (*param_1 == 0) {
      iVar2 = pm_get_in_port_rule_valid();
    }
    else {
      iVar2 = pm_get_out_port_rule_valid(param_1[2],&local_c);
    }
    if (iVar2 == 0) {
      if (local_c < 2) {
        param_1[1] = local_c;
      }
      uVar1 = 0;
    }
    else {
      if ((g_tm_debug_level != 0) && (iVar2 = ___ratelimit(_rs_7309,"pm_get_port_cfg"), iVar2 != 0))
      {
        printk("[TM][pm_get_port_cfg] failed\n");
      }
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][pm_set_port_cfg]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

