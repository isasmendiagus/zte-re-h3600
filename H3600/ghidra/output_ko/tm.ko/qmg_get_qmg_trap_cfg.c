// module: tm.ko
// function: qmg_get_qmg_trap_cfg @ 0x41aac
// size: 188 bytes
//

int qmg_get_qmg_trap_cfg(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(4,local_14,0,QmgRegTable);
  if (iVar1 == 0) {
    if (local_14[0] < 4) {
      *param_1 = local_14[0];
    }
    if (g_tm_debug_level < 7) {
      iVar1 = 0;
    }
    else {
      printk("[TM][qmg_get_qmg_trap_cfg]output: trap_cfg_val = %d\n",*param_1);
      iVar1 = 0;
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_6989,"qmg_get_qmg_trap_cfg"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/tm_qmg.c",0x1ad);
  }
  return iVar1;
}

