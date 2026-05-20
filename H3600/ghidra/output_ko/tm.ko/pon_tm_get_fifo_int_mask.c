// module: tm.ko
// function: pon_tm_get_fifo_int_mask @ 0x459f8
// size: 296 bytes
//

int pon_tm_get_fifo_int_mask(uint param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_tm_get_fifo_int_mask]input: FifoMsk=%d\n",param_1);
  }
  if (param_1 < 8) {
    iVar1 = tmOnuRegRead(0xd,local_1c,0,PonTmRegTable);
    if (iVar1 == 0) {
      *param_2 = local_1c[0] >> (param_1 & 0xff) & 1;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][pon_tm_get_fifo_int_mask]output: FifoIntMsk=%d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7219,"pon_tm_get_fifo_int_mask"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",0x402);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7216,"pon_tm_get_fifo_int_mask"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x3fb);
    }
    iVar1 = 1;
  }
  return iVar1;
}

