// module: tm.ko
// function: sadm_set_bucket_overspeed_en @ 0x240c8
// size: 328 bytes
//

undefined4 sadm_set_bucket_overspeed_en(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  uint local_14;
  
  bVar4 = param_2 != 0;
  bVar3 = param_2 == 1;
  if (param_2 < 2) {
    bVar4 = 6 < param_1;
    bVar3 = param_1 == 7;
  }
  local_14 = 0;
  if (!bVar4 || bVar3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_set_bucket_overpress_en]input:port_id = %d, overspeed_en = %d\n",param_1,
             param_2);
    }
    iVar2 = tmOnuRegRead(10,&local_14,0,sadmRegTable);
    if (iVar2 == 0) {
      local_14 = local_14 & ~(1 << (param_1 & 0xff)) | param_2 << (param_1 & 0xff);
      iVar2 = tmOnuRegWrite(10,local_14,0,sadmRegTable);
      uVar1 = 0;
      if (iVar2 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar2 = ___ratelimit(_rs_14379,"sadm_set_bucket_overspeed_en");
        if (iVar2 == 0) {
          return 0xffffffff;
        }
        printk("[TM][sadm_set_bucket_overpress_en]write reg failed!\n");
        return 0xffffffff;
      }
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_14377,"sadm_set_bucket_overspeed_en"), iVar2 == 0)) {
        return 0xffffffff;
      }
      printk("[TM][sadm_get_bucket_overpress_en]write reg failed!\n");
      uVar1 = 0xffffffff;
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_14374,"sadm_set_bucket_overspeed_en"), iVar2 != 0)) {
      printk("[TM][sadm_set_bucket_overpress_en]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  return uVar1;
}

