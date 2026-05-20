// module: tm.ko
// function: sadm_set_indacs_cmd @ 0x239f8
// size: 316 bytes
//

undefined4 sadm_set_indacs_cmd(uint param_1,uint param_2,int param_3,uint param_4,uint param_5)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar2 = 4 < param_2;
  if (param_2 < 6) {
    bVar2 = 0x3fffff < param_1;
  }
  if (!bVar2) {
    bVar3 = 6 < param_4;
    bVar2 = param_4 == 7;
    if (param_4 < 8) {
      bVar3 = param_3 != 0;
      bVar2 = param_3 == 1;
    }
    if (param_5 < 2 && (!bVar3 || bVar2)) {
      if ((6 < g_tm_debug_level) &&
         (printk("[TM][sadm_set_indacs_cmd]input:ram_addr = %d,mem_id = %d,rd = %d\n",param_1,
                 param_2,param_3), 6 < g_tm_debug_level)) {
        printk("[TM][sadm_set_indacs_cmd]input:auto_incr_size = %d,en = %d\n",param_4,param_5);
      }
      iVar1 = tmOnuRegWrite(6,param_5 << 0x1f | param_4 << 0x1c | param_3 << 0x1b | param_1 |
                              param_2 << 0x16,0,sadmRegTable);
      if (iVar1 != 0) {
        if ((g_tm_debug_level != 0) &&
           (iVar1 = ___ratelimit(_rs_14308,"sadm_set_indacs_cmd"), iVar1 != 0)) {
          printk("[TM][sadm_set_indacs_cmd]write reg failed!\n");
        }
        return 0xffffffff;
      }
      return 0;
    }
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_14305,"sadm_set_indacs_cmd"), iVar1 != 0)
     ) {
    printk("[TM][sadm_set_indacs_cmd]input invalid parameter!\n");
  }
  return 1;
}

