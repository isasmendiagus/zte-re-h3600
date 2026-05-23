// module: tm.ko
// function: red_get_up_out_share_max @ 0x42e24
// size: 200 bytes
//

char red_get_up_out_share_max(uint *param_1)

{
  char cVar1;
  int iVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  cVar1 = tmOnuRegRead(0xc,local_14,0,RedRegTable);
  if (cVar1 == '\0') {
    *param_1 = local_14[0] & 0x7fff;
    if ((g_tm_debug_level == 0) ||
       (iVar2 = ___ratelimit(_rs_7220,"red_get_up_out_share_max"), iVar2 == 0)) {
      return '\0';
    }
    printk("[TM][bppe_ptr_get]output: up_out_max=%d\n",*param_1);
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7217,"red_get_up_out_share_max"), iVar2 != 0)) {
    printk("[TM][bppe_ptr_set]read reg failed!\n");
  }
  return cVar1;
}

