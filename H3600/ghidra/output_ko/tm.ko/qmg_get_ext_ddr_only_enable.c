// module: tm.ko
// function: qmg_get_ext_ddr_only_enable @ 0x41750
// size: 168 bytes
//

int qmg_get_ext_ddr_only_enable(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(2,local_14,0,QmgRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][qmg_get_ext_ddr_only_enable]output: ext_ddr_en = %d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_6955,"qmg_get_ext_ddr_only_enable"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/tm_qmg.c",0x113);
  }
  return iVar1;
}

