// module: tm.ko
// function: pon_tm_get_jumbo_data_base_addr @ 0x44cb8
// size: 176 bytes
//

undefined4 pon_tm_get_jumbo_data_base_addr(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(6,local_14,0,PonTmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][pon_tm_get_jumbo_data_base_addr]output: DatAddr=%d\n");
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7084,"pon_tm_get_jumbo_data_base_addr"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_reg.c",0x22a);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

