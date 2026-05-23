// module: tm.ko
// function: qmg_set_qmg_up_ram_depth @ 0x41b74
// size: 224 bytes
//

int qmg_set_qmg_up_ram_depth(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][qmg_set_qmg_trap_cfg]input: up_ram_depth = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0x7ff < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_6996,"qmg_set_qmg_up_ram_depth"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/tm_qmg.c",0x1d1);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(5,param_1,0,QmgRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_6999,"qmg_set_qmg_up_ram_depth"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/tm_qmg.c",0x1d9);
    return iVar1;
  }
  return iVar1;
}

