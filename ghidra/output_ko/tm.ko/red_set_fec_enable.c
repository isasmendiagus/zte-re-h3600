// module: tm.ko
// function: red_set_fec_enable @ 0x42b90
// size: 224 bytes
//

char red_set_fec_enable(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][red_set_fec_enable]input: fec_en=%d\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) && (iVar2 = ___ratelimit(_rs_7190,"red_set_fec_enable"), iVar2 != 0)
       ) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_red.c",0x2b5);
    }
    return '\x01';
  }
  cVar1 = tmOnuRegWrite(0xb,param_1,0,RedRegTable);
  if (((cVar1 != '\0') && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7193,"red_set_fec_enable"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_red.c",0x2bd);
  }
  return cVar1;
}

