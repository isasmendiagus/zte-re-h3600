// module: tm.ko
// function: sadm_set_adm_en @ 0x23148
// size: 216 bytes
//

undefined4 sadm_set_adm_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(&_rs_14206,"sadm_set_adm_en"), iVar1 != 0))
    {
      printk("[TM][sadm_set_admen]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_admen]input:en = %d\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(0,param_1,0,sadmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_14209,"sadm_set_adm_en"), iVar1 != 0)) {
    printk("[TM][sadm_set_admen]write reg failed!\n");
  }
  return 0xffffffff;
}

