// module: tm.ko
// function: sadm_get_bucket_overspeed_threshold @ 0x24018
// size: 164 bytes
//

undefined4 sadm_get_bucket_overspeed_threshold(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(9,local_14,0,sadmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_get_bucket_overspeed_threshold]output:threshold = %d\n");
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14365,"sadm_get_bucket_overspeed_threshold"), iVar1 != 0)) {
      printk("[TM][sadm_get_bucket_overspeed_threshold]write reg failed!\n");
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

