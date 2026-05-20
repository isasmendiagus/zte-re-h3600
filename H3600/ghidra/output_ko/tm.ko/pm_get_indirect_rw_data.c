// module: tm.ko
// function: pm_get_indirect_rw_data @ 0x333ec
// size: 268 bytes
//

undefined4 pm_get_indirect_rw_data(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pm_get_indirect_rw_data]input: data_id = %d\n",param_1);
  }
  if (param_1 < 0xe) {
    iVar2 = tmOnuRegRead(2,&local_14,param_1,pmRegTable);
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_7145,"pm_get_indirect_rw_data"), iVar2 != 0)) {
        printk("[TM][pm_get_indirect_rw_data]reg read failed\n");
      }
      return 0xffffffff;
    }
    *param_2 = local_14;
    uVar1 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][pm_get_indirect_rw_data]output: rw_data = %d\n");
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7142,"pm_get_indirect_rw_data"), iVar2 != 0)) {
      printk("[TM][pm_get_indirect_rw_data]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  return uVar1;
}

