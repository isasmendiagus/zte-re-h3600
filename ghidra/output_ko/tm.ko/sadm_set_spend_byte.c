// module: tm.ko
// function: sadm_set_spend_byte @ 0x2434c
// size: 204 bytes
//

undefined4
sadm_set_spend_byte(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x3f < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14396,"sadm_set_spend_byte"), iVar1 != 0)) {
      printk("[TM][sadm_set_spend_byte]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_spend_byte]input:spend_byte = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  iVar1 = tmOnuRegWrite(0xb,param_1,0,sadmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_14399,"sadm_set_spend_byte"), iVar1 != 0)
     ) {
    printk("[TM][sadm_set_spend_byte]write reg failed!\n");
  }
  return 0xffffffff;
}

