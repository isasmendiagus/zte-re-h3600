// module: tm.ko
// function: red_get_fec_enable @ 0x42c80
// size: 168 bytes
//

int red_get_fec_enable(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0xb,local_14,0,RedRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][red_get_fec_enable]output: fec_en=%d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7200,"red_get_fec_enable"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_red.c",0x2de);
  }
  return iVar1;
}

