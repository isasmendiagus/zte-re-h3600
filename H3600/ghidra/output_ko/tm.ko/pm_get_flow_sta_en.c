// module: tm.ko
// function: pm_get_flow_sta_en @ 0x33f2c
// size: 132 bytes
//

undefined4 pm_get_flow_sta_en(uint *param_1)

{
  int iVar1;
  uint local_c;
  
  local_c = 0;
  iVar1 = tmOnuRegRead(8,&local_c,0,pmRegTable);
  if (iVar1 != 0) {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7266,"pm_get_flow_sta_en"), iVar1 != 0)
       ) {
      printk("[TM][pm_get_flow_sta_en]reg write failed\n");
    }
    return 0xffffffff;
  }
  *param_1 = local_c & 1;
  return 0;
}

