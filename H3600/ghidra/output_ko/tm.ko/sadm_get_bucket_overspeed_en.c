// module: tm.ko
// function: sadm_get_bucket_overspeed_en @ 0x24224
// size: 280 bytes
//

undefined4 sadm_get_bucket_overspeed_en(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_get_bucket_overspeed_en]input:port_id = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(10,local_1c,0,sadmRegTable);
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_14390,"sadm_get_bucket_overspeed_en"), iVar2 != 0)) {
        printk("[TM][sadm_get_bucket_overspeed_en]write reg failed!\n");
      }
      return 0xffffffff;
    }
    *param_2 = local_1c[0] >> (param_1 & 0xff) & 1;
    uVar1 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_get_bucket_overspeed_en]output:overspeed_en = %d\n");
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_14387,"sadm_get_bucket_overspeed_en"), iVar2 != 0)) {
      printk("[TM][sadm_get_bucket_overspeed_en]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  return uVar1;
}

