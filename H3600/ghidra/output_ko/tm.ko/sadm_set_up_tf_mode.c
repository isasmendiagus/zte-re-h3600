// module: tm.ko
// function: sadm_set_up_tf_mode @ 0x25250
// size: 204 bytes
//

int sadm_set_up_tf_mode(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (4 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14545,"sadm_set_up_tf_mode"), iVar1 != 0)) {
      printk("[TM][sadm_set_up_tf_mode]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_up_tf_mode]input: tf_mod = %d\n",param_1,param_3,g_tm_debug_level,param_4)
    ;
  }
  iVar1 = tmOnuRegWrite(0x13,param_1,0,sadmRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_14548,"sadm_set_up_tf_mode"), iVar2 != 0)) {
    printk("[TM][sadm_set_up_tf_mode]write reg failed!\n");
  }
  return iVar1;
}

