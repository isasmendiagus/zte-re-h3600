// module: tm.ko
// function: pon_tm_get_queue_int_state @ 0x44f6c
// size: 276 bytes
//

int pon_tm_get_queue_int_state(uint param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  uint local_14;
  
  local_14 = 0;
  if (param_1 < 3) {
    iVar1 = tmOnuRegRead(8,&local_14,0,PonTmRegTable);
    if (iVar1 == 0) {
      *param_2 = local_14 >> (param_1 & 0xff) & 1;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][pon_tm_get_queue_int_state]output: QueIntSta=%d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7118,"pon_tm_get_queue_int_state"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",0x2a2);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7115,"pon_tm_get_queue_int_state"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x29c);
    }
    iVar1 = 1;
  }
  return iVar1;
}

