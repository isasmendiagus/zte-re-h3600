// module: tm.ko
// function: pm_set_zte_cfg @ 0x3502c
// size: 220 bytes
//

undefined4 pm_set_zte_cfg(uint *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_c [8];
  
  if (((((param_1[1] < 2) && (*param_1 < 2)) && (param_1[3] < 8)) && (param_1[2] < 2)) &&
     ((*param_1 != 0 || (param_1[4] < 0xfff)))) {
    iVar2 = pm_select_zte_reg(param_1,0,auStack_c);
    uVar1 = 0;
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) && (iVar2 = ___ratelimit(_rs_7423,"pm_set_zte_cfg"), iVar2 != 0))
      {
        printk("[TM][pm_set_zte_cfg]failed\n");
      }
      return 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][pm_set_zte_cfg]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

