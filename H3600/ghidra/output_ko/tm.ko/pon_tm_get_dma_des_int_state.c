// module: tm.ko
// function: pon_tm_get_dma_des_int_state @ 0x45090
// size: 276 bytes
//

int pon_tm_get_dma_des_int_state(uint param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  uint local_14;
  
  local_14 = 0;
  if (param_1 < 2) {
    iVar1 = tmOnuRegRead(9,&local_14,0,PonTmRegTable);
    if (iVar1 == 0) {
      *param_2 = local_14 >> (param_1 & 0xff) & 1;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][pon_tm_get_dma_des_int_state]output: dma_int_sta=%d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7129,"pon_tm_get_dma_des_int_state"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",0x2c9);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7126,"pon_tm_get_dma_des_int_state"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x2c3);
    }
    iVar1 = 1;
  }
  return iVar1;
}

