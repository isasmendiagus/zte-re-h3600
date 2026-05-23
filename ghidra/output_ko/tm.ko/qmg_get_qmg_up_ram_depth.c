// module: tm.ko
// function: qmg_get_qmg_up_ram_depth @ 0x41c64
// size: 168 bytes
//

int qmg_get_qmg_up_ram_depth(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(5,local_14,0,QmgRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][qmg_get_qmg_up_ram_depth]output: up_ram_depth = %d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7006,"qmg_get_qmg_up_ram_depth"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/tm_qmg.c",0x1fa);
  }
  return iVar1;
}

