// module: tm.ko
// function: sadm_get_indacs_cmd @ 0x23b44
// size: 280 bytes
//

undefined4
sadm_get_indacs_cmd(uint *param_1,uint *param_2,uint *param_3,uint *param_4,uint *param_5)

{
  int iVar1;
  undefined4 uVar2;
  uint local_24 [2];
  
  local_24[0] = 0;
  iVar1 = tmOnuRegRead(6,local_24,0,sadmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_24[0] & 0x3fffff;
    *param_2 = (local_24[0] << 5) >> 0x1b;
    *param_3 = (local_24[0] << 4) >> 0x1f;
    *param_4 = (local_24[0] << 1) >> 0x1d;
    *param_5 = local_24[0] >> 0x1f;
    if ((g_tm_debug_level < 7) ||
       (printk("[TM][sadm_get_indacs_cmd]output:ram_addr = %d,mem_id = %d,rd = %d\n",*param_1,
               *param_2,*param_3), g_tm_debug_level < 7)) {
      return 0;
    }
    printk("[TM][sadm_get_indacs_cmd]output:auto_incr_size = %d,en = %d\n",*param_4,*param_5);
    uVar2 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14319,"sadm_get_indacs_cmd"), iVar1 != 0)) {
      printk("[TM][sadm_get_indacs_cmd]write reg failed!\n");
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

