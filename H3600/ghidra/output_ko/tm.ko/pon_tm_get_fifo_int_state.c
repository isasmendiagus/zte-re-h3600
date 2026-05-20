// module: tm.ko
// function: pon_tm_get_fifo_int_state @ 0x451b4
// size: 356 bytes
//

undefined4 pon_tm_get_fifo_int_state(uint param_1,uint *param_2)

{
  int iVar1;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (g_tm_debug_level == 0) {
    if (param_1 < 8) {
LAB_000451f4:
      iVar1 = tmOnuRegRead(10,local_1c,0,PonTmRegTable);
      if (iVar1 != 0) {
        if ((g_tm_debug_level != 0) &&
           (iVar1 = ___ratelimit(_rs_7142,"pon_tm_get_fifo_int_state"), iVar1 != 0)) {
          printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_reg.c",0x2f4);
        }
        return 0xffffffff;
      }
      *param_2 = local_1c[0] >> (param_1 & 0xff) & 1;
      if ((g_tm_debug_level != 0) &&
         (iVar1 = ___ratelimit(_rs_7144,"pon_tm_get_fifo_int_state"), iVar1 != 0)) {
        printk("[TM][pon_tm_get_fifo_int_state]output: IntSta = %d\n",*param_2);
        return 0;
      }
      return 0;
    }
  }
  else {
    iVar1 = ___ratelimit(_rs_7137,"pon_tm_get_fifo_int_state");
    if (iVar1 != 0) {
      printk("[TM][pon_tm_get_fifo_int_state]input: fifo_msk=%d,\n",param_1);
    }
    if (param_1 < 8) goto LAB_000451f4;
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7140,"pon_tm_get_fifo_int_state"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x2ed);
    }
  }
  return 1;
}

